/*
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 */
/** @file MinerPrecompiled.h
 *  @author ancelmo
 *  @date 20180921
 */
#pragma once

#include "Storage.h"
#include "StorageException.h"
#include "Table.h"
#include <json/json.h>
#include <leveldb/db.h>
#include <libdevcore/FixedHash.h>
#include <libdevcore/Guards.h>
namespace dev
{
namespace storage
{
class LevelDBStorage : public Storage
{
public:
    typedef std::shared_ptr<LevelDBStorage> Ptr;

    virtual ~LevelDBStorage(){};

    virtual Entries::Ptr select(
        h256 hash, int num, const std::string& table, const std::string& key) override;
    virtual size_t commit(
        h256 hash, int64_t num, const std::vector<TableData::Ptr>& datas, h256 blockHash) override;
    virtual bool onlyDirty() override;

    void setDB(std::shared_ptr<leveldb::DB> db);

private:
    std::shared_ptr<leveldb::DB> m_db;
    dev::SharedMutex m_remoteDBMutex;
};

}  // namespace storage

}  // namespace dev
