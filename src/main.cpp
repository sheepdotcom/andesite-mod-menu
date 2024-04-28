#include "client.hpp"

using namespace geode::prelude;

Client* client;

//Hack setup will now go here!
$execute{
	client = new Client();
	Client::instance = client;

	Client::Setup();
}