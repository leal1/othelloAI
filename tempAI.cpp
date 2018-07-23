#include <ics46/factory/DynamicFactory.hpp>
#include "tempAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, leal1::tempAI, "55131 AI (Required)");

std::pair<int,int> leal1::tempAI::chooseMove(const OthelloGameState& state)
{
  turn = ((state.isBlackTurn()) ? color::black : color::white);
  std::vector<std::pair<int,int>> validMovesVector = validMoves(state);
  std::pair<int,int> bestMove (-1,-1);
  int bestValue = -9999999;
  for(int i = 0; i < validMovesVector.size(); i++)
  {
    int move_value = get_move_value(state, validMovesVector, 8, i);
    if(move_value > bestValue)
    {
      bestMove.first = validMovesVector[i].first;
      bestMove.second = validMovesVector[i].second;
      bestValue = move_value;
    }
  }
  return bestMove;
}
bool leal1::tempAI::AI_turn(const OthelloGameState& state)
{
  if((turn == color::black && state.isBlackTurn() == true)
      || (turn == color::white && state.isWhiteTurn() == true))
      {
        return true;
      }
  return false;
}


int leal1::tempAI::search(const OthelloGameState& state, int depth)
{
  if (depth <= 0)
  {
    return evaluate(state);
  }
  else
  {
    std::vector<std::pair<int,int>> validMovesVector = validMoves(state);
    if(validMovesVector.size() == 0)
    {
      return evaluate(state);
    }
    if(AI_turn(state))
    {
      int best_eval = -9999999;
      for(int i = 0; i < validMovesVector.size() ; i++ )
      {
        int val = get_move_value(state, validMovesVector, --depth, i);
        if( val > best_eval )
        {
          best_eval = val;
        }
      }
      return best_eval;
    }
    else if (!AI_turn(state))
    {
      int best_eval = 9999999;
      for(int i = 0; i < validMovesVector.size() ; i++ )
      {
        int val = get_move_value(state, validMovesVector, --depth, i);
        if( val < best_eval )
        {
          best_eval = val;
        }
      }
      return best_eval;
    }
  }
}

int leal1::tempAI::evaluate(const OthelloGameState& state)
{
  int width = state.board().width();
  int height = state.board().height();
  std::vector<std::pair<int,int>> worst_cells = {std::make_pair(1,1), std::make_pair(1, height - 2),
                                              std::make_pair( width - 2, 1),
                                              std::make_pair(width -2, height -2 )};

  std::vector<std::pair<int,int>> bad_cells = {std::make_pair(1,0), std::make_pair(0,1),
                                              std::make_pair(width - 2, 0),
                                              std::make_pair(width -1, 1),
                                              std::make_pair( 0, height - 2),
                                              std::make_pair(1, height -1),
                                              std::make_pair(width - 1, height -2),
                                              std::make_pair(width -2, height - 1) };

  std::vector<std::pair<int,int>> corners = {std::make_pair(0,0), std::make_pair(width-1, height-1),
                                              std::make_pair(0, height-1), std::make_pair(width-1, 0)};
  int value = ((turn == color::black) ? (state.blackScore() - state.whiteScore())
                                      : (state.whiteScore() - state.blackScore()));
  for(int i = 0; i < worst_cells.size(); i++)
  {
    if(state.board().cellAt(worst_cells[i].first, worst_cells[i].second) == OthelloCell::black)
    {
      value += ( ( turn == color::black) ? (-5) : (0));
    }
  }

  for(int i = 0; i < bad_cells.size(); i++)
  {
    if(state.board().cellAt(bad_cells[i].first, bad_cells[i].second) == OthelloCell::black)
    {
      value += ( ( turn == color::black) ? (-2) : (0));
    }
  }
  return value;

  for(int i = 0; i < corners.size(); i++)
  {
    if(state.board().cellAt(corners[i].first, corners[i].second) == OthelloCell::black)
    {
      value+= ( ( turn == color::black) ? (5) : (-5)) ;
    }
  }



}

int leal1::tempAI::get_move_value(const OthelloGameState& state, std::vector<std::pair<int,int>> move_vector
                                  , int depth, int i)
{
  std::unique_ptr<OthelloGameState> state_ptr = state.clone();
  state_ptr -> makeMove(move_vector[i].first, move_vector[i].second);
  return search(*state_ptr, depth);
}
std::vector<std::pair<int,int>> leal1::tempAI::validMoves(const OthelloGameState& state)
{
  std::vector<std::pair<int,int>> validMoves;
  for(int col = 0; col < (state.board()).width(); col++)
  {
    for(int row = 0; row < (state.board()).height(); row++)
    {
      if(state.isValidMove(col,row))
      {
        validMoves.push_back(std::make_pair(col,row));
      }
    }
  }
  return validMoves;
}
