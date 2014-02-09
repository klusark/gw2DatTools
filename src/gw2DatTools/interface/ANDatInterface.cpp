#include "gw2DatTools/interface/ANDatInterface.h"

#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "gw2DatTools/exception/Exception.h"

#include "../format/ANDat.h"
#include "../format/Mft.h"
#include "../format/Mapping.h"
#include "../format/Utils.h"

namespace gw2dt
{
namespace interface
{

class ANDatInterfaceImpl : public ANDatInterface
{
    public:
        ANDatInterfaceImpl(const char* iDatPath, std::unique_ptr<format::Mft>& ipMft, std::unique_ptr<format::Mapping>& ipMapping);
        virtual ~ANDatInterfaceImpl();
        
        virtual void getBuffer(const ANDatInterface::FileRecord& iFileRecord, uint32_t& ioOutputSize, uint8_t* ioBuffer);
        
        virtual const FileRecord& getFileRecordForBaseId(const uint32_t& iBaseId) const;
        
        virtual const std::vector<FileRecord>& getFileRecordVect() const;
        
    private:
        std::ifstream _datStream;
        
        // Computed data structures
        std::vector<FileRecord> _fileRecordVect;
        
        // Raw data structures
        std::unique_ptr<format::Mft> _pMft;
        std::unique_ptr<format::Mapping> _pMapping;
};

ANDatInterfaceImpl::ANDatInterfaceImpl(const char* iDatPath, std::unique_ptr<format::Mft>& ipMft, std::unique_ptr<format::Mapping>& ipMapping) :
    _datStream(iDatPath, std::ios::binary),
    _pMft(std::move(ipMft)),
    _pMapping(std::move(ipMapping))
{
}

ANDatInterfaceImpl::~ANDatInterfaceImpl()
{
}

void ANDatInterfaceImpl::getBuffer(const ANDatInterface::FileRecord& iFileRecord, uint32_t& ioOutputSize, uint8_t* ioBuffer)
{
    _datStream.seekg(iFileRecord.offset);
    ioOutputSize = std::min(ioOutputSize, iFileRecord.size);
    format::readStructs(_datStream, *ioBuffer, ioOutputSize);
}

const ANDatInterface::FileRecord& ANDatInterfaceImpl::getFileRecordForBaseId(const uint32_t& iBaseId) const
{
	int id = 0;
	for (uint32_t i = 0; i < _pMapping->entries.size(); ++i) {
		auto m = _pMapping->entries[i];
		if (m.id == iBaseId) {
			id = m.mftIndex;
		}
	}
	auto &entry = _pMft->entries[id - 1];
	FileRecord *aFileRecord = new FileRecord();
	aFileRecord->offset = entry.offset;
	aFileRecord->isCompressed = (bool)entry.compressionFlag;
	aFileRecord->size = entry.size;
	return *aFileRecord;
   /* auto it = _baseIdDict.find(iBaseId);
    if (it != _baseIdDict.end())
    {
        if (it->second != nullptr)
        {
            return *(it->second);
        }
        else
        {
            throw exception::Exception("BaseId found, but null entry.");
        }
    }
    else
    {
        throw exception::Exception("BaseId not found.");
    }*/
}

const std::vector<ANDatInterface::FileRecord>& ANDatInterfaceImpl::getFileRecordVect() const
{
    return _fileRecordVect;
}

GW2DATTOOLS_API std::unique_ptr<ANDatInterface> GW2DATTOOLS_APIENTRY createANDatInterface(const char* iDatPath)
{
    std::ifstream aDatStream(iDatPath, std::ios::binary);
    auto pANDat = format::parseANDat(aDatStream, 0, 0);
    
    auto pMft = format::parseMft(aDatStream, pANDat->header.mftOffset, pANDat->header.mftSize);
    auto pMapping = format::parseMapping(aDatStream, pMft->entries[1].offset, pMft->entries[1].size);

    
    auto pANDatInterfaceImpl = std::unique_ptr<ANDatInterfaceImpl>(new ANDatInterfaceImpl(iDatPath, pMft, pMapping));
    
    return std::move(pANDatInterfaceImpl);
}

}
}
