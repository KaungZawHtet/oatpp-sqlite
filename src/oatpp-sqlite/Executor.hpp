/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_sqlite_Executor_hpp
#define oatpp_sqlite_Executor_hpp

#include "ConnectionProvider.hpp"
#include "QueryResult.hpp"

#include "mapping/Serializer.hpp"
#include "mapping/TypeMapper.hpp"
#include "mapping/ResultMapper.hpp"

#include "oatpp/orm/Executor.hpp"
#include "oatpp/core/parser/Caret.hpp"

#include <vector>

namespace oatpp { namespace sqlite {

class Executor : public orm::Executor {
private:
  void bindParams(sqlite3_stmt* stmt,
                  const StringTemplate& queryTemplate,
                  const std::unordered_map<oatpp::String, oatpp::Void>& params);

  std::shared_ptr<orm::QueryResult> exec(const oatpp::String& statement,
                                         const std::shared_ptr<orm::Connection>& connection = nullptr);

  oatpp::String getSchemaVersionTableName(const oatpp::String& suffix);
  std::shared_ptr<orm::QueryResult> updateSchemaVersion(v_int64 newVersion,
                                                        const oatpp::String& suffix,
                                                        const std::shared_ptr<orm::Connection>& connection);

private:
  std::shared_ptr<provider::Provider<Connection>> m_connectionProvider;
  std::shared_ptr<mapping::ResultMapper> m_resultMapper;
  mapping::TypeMapper m_typeMapper;
  mapping::Serializer m_serializer;
public:

  Executor(const std::shared_ptr<provider::Provider<Connection>>& connectionProvider);

  StringTemplate parseQueryTemplate(const oatpp::String& name,
                                    const oatpp::String& text,
                                    const ParamsTypeMap& paramsTypeMap,
                                    bool prepare) override;

  std::shared_ptr<orm::Connection> getConnection() override;

  std::shared_ptr<orm::QueryResult> execute(const StringTemplate& queryTemplate,
                                            const std::unordered_map<oatpp::String, oatpp::Void>& params,
                                            const std::shared_ptr<orm::Connection>& connection) override;

  std::shared_ptr<orm::QueryResult> begin(const std::shared_ptr<orm::Connection>& connection = nullptr) override;

  std::shared_ptr<orm::QueryResult> commit(const std::shared_ptr<orm::Connection>& connection) override;

  std::shared_ptr<orm::QueryResult> rollback(const std::shared_ptr<orm::Connection>& connection) override;

  v_int64 getSchemaVersion(const oatpp::String& suffix = nullptr,
                           const std::shared_ptr<orm::Connection>& connection = nullptr) override;

  void migrateSchema(const oatpp::String& script,
                     v_int64 newVersion,
                     const oatpp::String& suffix = nullptr,
                     const std::shared_ptr<orm::Connection>& connection = nullptr) override;

};

}}

#endif // oatpp_sqlite_Executor_hpp
