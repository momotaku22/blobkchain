#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>





class Bloc
{
public:
    long heuroDatage;
    int identifiant;
    std::string data;
    std::string hachage;
    std::string hachageAncien;

    Bloc(int _identifiant, std::string _data, std::string _hachage, std::string _hachageAncien, long _heuroDatage)
        : identifiant(_identifiant), data(_data), hachage(_hachage), hachageAncien(_hachageAncien), heuroDatage(_heuroDatage) {};
};

std::string genererHachage(int identifiant, std::string hachageAncien, long heuroDatage, std::string data)
{
    std::ostringstream flux;
    flux << identifiant << hachageAncien << heuroDatage << data;
    return std::to_string(std::hash<std::string>{}(flux.str()));
}

Bloc creerBlock()
{
    long heuroDatageInitial = std::time(nullptr);
    std::string hachageGenesis = genererHachage(0, "0", heuroDatageInitial, "BlocGenesis");
    return Bloc(0, "BlocGenesis", hachageGenesis, "0", heuroDatageInitial);
}

Bloc creerNouveauBlock(const Bloc& blocAncien, const std::string& data)
{
    int nouveauIdentifiant = blocAncien.identifiant + 1;  
    long heuroDatageInitial = std::time(nullptr);
    std::string hachagePrecedent = blocAncien.hachage;
    std::string hachageNouveau = genererHachage(nouveauIdentifiant, hachagePrecedent, heuroDatageInitial, data);
    return Bloc(nouveauIdentifiant, data, hachageNouveau, hachagePrecedent, heuroDatageInitial);
}

int main()
{
    std::vector<Bloc> Blockchain;

  
    Bloc blocGenesis = creerBlock();
    Blockchain.push_back(blocGenesis);

    std::string donneesPremierBloc = "data creer";
    Bloc premierBloc = creerNouveauBlock(blocGenesis, donneesPremierBloc);
    Blockchain.push_back(premierBloc);


    for (const Bloc& bloc : Blockchain)
    {
        std::cout << "Bloc ID: " << bloc.identifiant << "\n";
        std::cout << "Data: " << bloc.data << "\n";
        std::cout << "Hachage: " << bloc.hachage << "\n";
        std::cout << "Hachage Ancien: " << bloc.hachageAncien << "\n";
        std::cout << "Heuro Datage: " << bloc.heuroDatage << "\n\n";
    }
    return 0;

    
}
