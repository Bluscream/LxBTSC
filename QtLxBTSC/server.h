#pragma once
#include "client.h"
#include <teamspeak/public_rare_definitions.h>
#include <QMap>

class Server
{
public:
	Server(uint64 serverid, QString uid, QMap<anyID, Client> clients)
	{
		this->clients_ = clients;
		this->server_connection_handler_id_ = serverid;
		this->uid_ = uid;
		this->safe_uid_ = uid.replace(QRegExp("[+/=]"), "00");
	}
	Server() : uid_("") {}
	~Server() {}

	void Server::set_clients(QMap<anyID, Client> clients)
	{
		clients_ = clients;
	}

	void Server::add_client(anyID clientID, Client client)
	{
		clients_.insert(clientID, client);
	}

	// this is the uid teamspeak uses
	QString Server::uid() const
	{
		return uid_;
	}

	// this uid works in html by replacing bad characters
	QString Server::safe_uid() const
	{
		return safe_uid_;
	}

	uint64 Server::server_connection_handler_id() const
	{
		return server_connection_handler_id_;
	}

	Client Server::get_client(anyID clientID) const
	{
		return clients_.value(clientID);
	}

	Client Server::get_client_by_nickname(const QString &nickname) const
	{
		for each (const Client & c in clients_)
		{
			if (c.nickname() == nickname)
			{
				return c;
			}
		}
		return Client("", "", 0);
	}

	bool operator==(const Server & server) const
	{
		return this->uid_ == server.uid();
	}

private:
	QMap<anyID, Client> clients_;
	uint64 server_connection_handler_id_;
	QString uid_;
	QString safe_uid_;
};
