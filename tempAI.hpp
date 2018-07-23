#include "OthelloAI.hpp"

#ifndef TEMPAI_HPP
#define TEMPAI_HPP

namespace leal1
{
  class tempAI : public OthelloAI
  {
  public:
    virtual std::pair<int,int> chooseMove(const OthelloGameState& state);

    int search(const OthelloGameState& state,  int depth);
    int evaluate(const OthelloGameState& state);

    std::vector<std::pair<int,int>> validMoves(const OthelloGameState& state);

    bool AI_turn(const OthelloGameState& state);
    int get_move_value(const OthelloGameState& state, std::vector<std::pair<int,int>> move_vector,
                                              int depth ,int i);


  private:
    enum class color {white, black};
    color turn;
  };
}

#endif
