#pragma once
#include <string>
class notepad{
	public:
			
		void deleteLine(std::string fileDirectory);
		void initilizeNotePad(std::string time);
        void writeMove(std::string time, int turn, std::string startMove, std::string endMove, char promotionPiece);
		int getTotalTurn(std::string fileDirectory);
		std::string getStartMove(std::string fileDirectory, int turn);
		std::string getEndMove(std::string fileDirectory, int turn);
        std::string getPromotionPiece(std::string fileDirectory, int turn);

        std::string returnGameList();
};
