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

#ifndef oatpp_sqlite_ConnectionProvider_hpp
#define oatpp_sqlite_ConnectionProvider_hpp

#include "Connection.hpp"

#include "oatpp/core/provider/Pool.hpp"
#include "oatpp/core/Types.hpp"

namespace oatpp { namespace sqlite {

/**
 * Connection provider.
 */
class ConnectionProvider : public provider::Provider<Connection> {
private:
  oatpp::String m_connectionString;
public:

  /**
   * Constructor.
   * @param connectionString
   */
  ConnectionProvider(const oatpp::String& connectionString);

  /**
   * Get Connection.
   * @return - resource.
   */
  std::shared_ptr<Connection> get() override;

  /**
   * Get Connection in Async manner.
   * @return - &id:oatpp::async::CoroutineStarterForResult; of `Connection`.
   */
  async::CoroutineStarterForResult<const std::shared_ptr<Connection>&> getAsync() override;

  /**
   * Invalidate Connection that was previously created by this provider. <br>
   * @param resource
   */
  void invalidate(const std::shared_ptr<Connection>& resource) override;

  /**
   * Stop provider and free associated resources.
   */
  void stop() override;

};

/**
 * Connection pool. <br>
 * - &id:oatpp::sqlite::Connection;.
 * - &id:oatpp::sqlite::ConnectionAcquisitionProxy;.
 */
typedef oatpp::provider::Pool<
  provider::Provider<Connection>,
  Connection,
  ConnectionAcquisitionProxy
> ConnectionPool;

}}

#endif // oatpp_sqlite_ConnectionProvider_hpp