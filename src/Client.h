#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>

struct Client {
    int id;
    std::string nom;
    std::string prenom;
    std::string email;
    std::string telephone;
    std::string date_inscription;
};

class ClientManager {
public:
    static std::vector<Client> listClients();
    static void addClient(const Client& client);
    static void updateClient(const Client& client);
    static void deleteClient(int clientId);
    static std::vector<Client> searchClients(const std::string& filter);
};

#endif // CLIENT_H
