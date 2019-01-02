//
// Created by baha2 on 1/2/2019.
//

#ifndef WET2_SCORESVALUE_H
#define WET2_SCORESVALUE_H
#define NOT_INITIALIZED -1
class ScoresValue {
public:
    int score;
    int maxLeftScore;
    int maxRightScore;

    ScoresValue() : score(NOT_INITIALIZED),maxLeftScore(NOT_INITIALIZED),maxRightScore(NOT_INITIALIZED) {}

};
#endif //WET2_SCORESVALUE_H
