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

	Bloc(int _identifiant, std::string _data, std::string _hachage, std::string _hachageAncien, long hDatage)
		:identifiant(_identifiant), data(_data), hachage(_hachage), hachageAncien(_hachageAncien) {};
};


std::string genererHachage(int identifiant, std::string hachageAncien, long heuroDatage, std::string data)
{
	std::ostringstream flux;
	flux << identifiant << hachageAncien << heuroDatage << data;
	return std::to_string(std::hash<std::string>{}(flux.str()));
};

Bloc creerBlock()
{
	long heurodatageInitial = std::time(nullptr);
	std::string hachageGenesis = genererHachage(0, "0", heurodatageInitial, "BlocGenesis");
	//Bloc(int _identifiant, std::string _data, std::string _hachage, std::string _hachageAncien, long hDatage)
	return Bloc(1, "0", hachageGenesis, "BlocGenesis", heurodatageInitial);


};
Bloc creerNouveauBlock(const Bloc& blocAncien, const std::string& data)
{
	int nouveauIdentifiant;
	nouveauIdentifiant = blocAncien.identifiant;
	long heurodatageInitial = std::time(nullptr);
	std::string hachagePrecedent = blocAncien.hachage;
	std::string hachageNouveau = genererHachage(nouveauIdentifiant, hachagePrecedent, heurodatageInitial, data);
	//Bloc(int _identifiant, std::string _data, std::string _hachage, std::string _hachageAncien, long hDatage)
	return Bloc(nouveauIdentifiant, data, hachagePrecedent, hachageNouveau, heurodatageInitial);

};



int main()
{
	std::vector<Bloc> Blockchain;

	Bloc blocGenesis = creerNouveauBlock();
	Blockchain.push_back(blocGenesis);
	std::string donneesPremierBloc = "data creer";
	Bloc premierBloc = creerNouveauBlock(blocGenesis, donneesPremierBloc);
	Blockchain.push_back(premierBloc);
};