/**
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
 *
 * @brief: empty framework for main of lab-bcos
 *
 * @file: p2p_main.cpp
 * @author: yujiechen
 * @date 2018-09-10
 */

#include <initializer/Initializer.h>
#include <initializer/P2PInitializer.h>
#include <libdevcore/easylog.h>
#include <stdlib.h>

INITIALIZE_EASYLOGGINGPP

using namespace dev;
using namespace dev::initializer;

class P2PMessageFactory : public MessageFactory
{
public:
    virtual ~P2PMessageFactory() {}
    virtual Message::Ptr buildMessage() override { return std::make_shared<Message>(); }
};

int main(int argc, const char* argv[])
{
    auto initialize = std::make_shared<Initializer>();
    initialize->init("./config.conf");

    auto p2pInitializer = initialize->p2pInitializer();
    auto p2pService = p2pInitializer->p2pService();
    p2pService->setMessageFactory(std::make_shared<P2PMessageFactory>());

    uint32_t counter = 0;
    while (true)
    {
        std::shared_ptr<std::vector<std::string>> topics = p2pService->topics();
        std::string topic = "Topic" + to_string(counter++);
        topics->push_back(topic);
        LOG(INFO) << "Add topic periodically, now Topics[" << topics->size() - 1 << "]:" << topic;
        p2pService->setTopics(topics);
        this_thread::sleep_for(chrono::milliseconds((rand() % 50) * 100));
    }

    return 0;
}
