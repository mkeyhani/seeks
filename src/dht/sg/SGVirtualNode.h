/**
 * This is the p2p messaging component of the Seeks project,
 * a collaborative websearch overlay network.
 *
 * Copyright (C) 2010  Emmanuel Benazera, juban@free.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SGVIRTUALNODE_H
#define SGVIRTUALNODE_H

#include "DHTVirtualNode.h"
#include "sg_manager.h"
#include "l2_protob_wrapper.h"

namespace dht
{
  class SGNode;

  class SGVirtualNode : public DHTVirtualNode
  {
    public:
      SGVirtualNode(Transport *transport, sg_manager *sgm);

      SGVirtualNode(Transport *transport, sg_manager *sgm, const DHTKey &idkey);

      ~SGVirtualNode();

      virtual void execute_callback(const uint32_t &fct_id,
                                    const DHTKey &sender_key,
                                    const NetAddress &sender_na,
                                    const DHTKey &node_key,
                                    int& status,
                                    std::string &resp_msg,
                                    const std::string &inc_msg);

      /*- RPC callbacks. -*/
      void RPC_subscribe_cb(const DHTKey &senderKey,
                            const NetAddress &sender,
                            const DHTKey &sgKey,
                            std::vector<Subscriber*> &peers,
                            int &status);

      void RPC_replicate_cb(const DHTKey &senderKey,
                            const NetAddress &sender,
                            const DHTKey &ownerKey,
                            const std::vector<Searchgroup*> &sgs,
                            const bool &sdiff,
                            int &status);

      // call and response.
      void RPC_call2(const uint32_t &fct_id,
                     const DHTKey &recipientKey,
                     const NetAddress &recipient,
                     const DHTKey &sgKey,
                     l2::l2_subscribe_response *l2r) throw (dht_exception);

      void RPC_call2(const uint32_t &fct_id,
                     const DHTKey &recipientKey,
                     const NetAddress &recipient,
                     const DHTKey &senderKey,
                     const NetAddress &sender,
                     const DHTKey &sgKey,
                     l2::l2_subscribe_response *l2r) throw (dht_exception);

      void RPC_call2(const uint32_t &fct_id,
                     const DHTKey &recipientKey,
                     const NetAddress &recipient,
                     const DHTKey &senderKey,
                     const NetAddress &sender,
                     const DHTKey &ownerKey,
                     const std::vector<Searchgroup*> &sgs,
                     const bool &sdiff,
                     l1::l1_response *l1r) throw (dht_exception);

      void RPC_call2(const std::string &msg_str,
                     const DHTKey &recipientKey,
                     const NetAddress &recipient,
                     l2::l2_subscribe_response *l2r) throw (dht_exception);

      /*- l2 interface. -*/
      virtual void RPC_subscribe(const DHTKey &recipientKey,
                                 const NetAddress &recipient,
                                 const DHTKey &senderKey,
                                 const NetAddress &senderAddress,
                                 const DHTKey &sgKey,
                                 std::vector<Subscriber*> &peers,
                                 int &status) throw (dht_exception);

      virtual void RPC_replicate(const DHTKey &recipientKey,
                                 const NetAddress &recipient,
                                 const DHTKey &senderKey,
                                 const NetAddress &senderAddress,
                                 const DHTKey &ownerKey,
                                 const std::vector<Searchgroup*> &sgs,
                                 const bool &sdiff,
                                 int &status) throw (dht_exception);
      /**
       * replication of content.
       */

      /**
       * TODO.
       * \brief some replicated keys we host are ours now, let us move
       * them to the correct db.
       */
      virtual dht_err replication_host_keys(const DHTKey &start_key);

      virtual void replication_move_keys_backward(const DHTKey &start_key,
          const DHTKey &end_key,
          const NetAddress &senderAddress);

      virtual void replication_move_keys_forward(const DHTKey &end_key);

      virtual void replication_trickle_forward(const DHTKey &start_key,
          const short &start_replication_radius);

    public:
      sg_manager *_sgm;
  };

} /* end of namespace. */

#endif