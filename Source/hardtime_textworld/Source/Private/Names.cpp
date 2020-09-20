#include "Names.h"

std::string RandomName()
{
	std::string nickName;
	std::string lastName;
	std::string playerName;
	int random = rand() % 115;
	if (random < 4)
		nickName = "Mechanical";
	else if (random < 8)
		nickName = "Sharps";
	else if (random < 12)
		nickName = "Hazy-eye";
	else if (random < 16)
		nickName = "Flopsy";
	else if (random < 20)
		nickName = "Tender";
	else if (random < 24)
		nickName = "Lil'";
	else if (random < 28)
		nickName = "Stingy";
	else if (random < 32)
		nickName = "Juggernaught";
	else if (random < 36)
		nickName = "Prince";
	else if (random < 40)
		nickName = "Aftershock";
	else if (random < 44)
		nickName = "Mainline";
	else if (random < 48)
		nickName = "Cassanova";
	else if (random < 52)
		nickName = "Furious";
	else if (random < 58)
		nickName = "Manic";
	else if (random < 62)
		nickName = "Stinkin'";
	else if (random < 66)
		nickName = "Black-heart";
	else if (random < 70)
		nickName = "Honest";
	else if (random < 74)
		nickName = "Gardener";
	else if (random < 78)
		nickName = "Chairleg";
	else if (random < 82)
		nickName = "Butcher";
	else if (random < 86)
		nickName = "Blackjack";
	else if (random < 90)
		nickName = "Rasputin";
	else if (random < 94)
		nickName = "Chicago";
	else if (random < 98)
		nickName = "Dark fruits";
	else
	nickName = "";

	random = rand() % 100;
	if (random < 4)
		lastName = "Elliot";
	else if (random < 8)
		lastName = "White";
	else if (random < 12)
		lastName = "Bhopal";
	else if (random < 16)
		lastName = "Feng";
	else if (random < 20)
		lastName = "Mason";
	else if (random < 24)
		lastName = "Stone";
	else if (random < 28)
		lastName = "Kelly";
	else if (random < 32)
		lastName = "Wallace";
	else if (random < 36)
		lastName = "Green";
	else if (random < 40)
		lastName = "Rashid";
	else if (random < 44)
		lastName = "O' Leary";
	else if (random < 48)
		lastName = "McAlister";
	else if (random < 52)
		lastName = "McGinn";
	else if (random < 58)
		lastName = "Browne";
	else if (random < 62)
		lastName = "Wong";
	else if (random < 66)
		lastName = "Chiu";
	else if (random < 70)
		lastName = "Mammadov";
	else if (random < 74)
		lastName = "Lopez";
	else if (random < 78)
		lastName = "Garcia";
	else if (random < 82)
		lastName = "Wilson";
	else if (random < 86)
		lastName = "Nguyen";
	else if (random < 90)
		lastName = "Cohen";
	else if (random < 94)
		lastName = "Tanaka";
	else if (random < 98)
		lastName = "Park";
	else
	lastName = "DeSantos";

	if (nickName == "")
		playerName = lastName;
	else
		playerName = "\"" + nickName + "\" " + lastName;

	return playerName;
}