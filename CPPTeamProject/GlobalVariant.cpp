#include "GlobalVariant.h"

void GlobalVariant::initTotalBlock() {
/**
 * So, This iteration does:
 * 1. Every i, for j = 0, j = 13, set its var to 1.
 */
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if ((j == 0) || (j == 13)) {
                total_block[i][j] = 1;
            } else {
                total_block[i][j] = 0;
            }
        }
    }

    for (int j = 0; j < 14; j++)			//ȭ���� ���� ���� ���� 1�� ä���.
        total_block[20][j] = 1;
    // Afterall, those Iteration could minimize(or combine)
    // And those two for-operation does make some kind of beaker-shape array.
}

GlobalVariant::GlobalVariant() {
}

int GlobalVariant::getLevel() const {
    return this->level;
}

int GlobalVariant::getAbsoluteX() const {
    return this->ab_x;
}

int GlobalVariant::getAbsoluteY() const {
    return this->ab_y;
}

int GlobalVariant::getCtr() const {
    return this->ctr;
}

int& GlobalVariant::getNextBlockShape() {
    return this->next_block_shape;
}

int& GlobalVariant::getBlockAngle() {
    return this->block_angle;
}

int& GlobalVariant::getBlockX() {
    return this->block_x;
}

int& GlobalVariant::getBlockY() {
    return this->block_y;
}

int& GlobalVariant::getBlockShape() {
    return this->block_shape;
}

int GlobalVariant::getLine() const {
    return this->lines;
}

int GlobalVariant::getScore() const {
    return this->score;
}

int GlobalVariant::getGameOver() const {
    return this->is_gameover;
}

int* GlobalVariant::getPtrBlockAngle() {
    return &(this->block_angle);
}

int* GlobalVariant::getPtrBlockX() {
    return &(this->block_x);
}

int* GlobalVariant::getPtrBlockY() {
    return &(this->block_y);
}

int* GlobalVariant::getPtrBlockShape() {
    return &(this->block_shape);
}

int* GlobalVariant::getPtrNextBlockShape() {
    return &(this->next_block_shape);
}

char(*GlobalVariant::getTotalBlock())[14] {
    return this->total_block;
}

StageInformation(*GlobalVariant::getStageInformation()) {
    return this->stage_data;
}

void GlobalVariant::setBlockShape(const int& blockShape) {
    this->block_shape = blockShape;
}

void GlobalVariant::setNextBlockShape(const int& nextBlock) {
    this->next_block_shape = nextBlock;
}

void GlobalVariant::setBlockAngle(const int& blockangle) {
    this->block_angle = blockangle;
}

void GlobalVariant::setBlockX(const int& blox) {
    this->block_x = blox;
}

void GlobalVariant::setCtr(const int& ct) {
    this->ctr = ct;
}

void GlobalVariant::setLine(const int& ln) {
    this->lines = ln;
}

void GlobalVariant::setScore(const int& sc) {
    this->score = sc;
}

void GlobalVariant::setLevel(const int& lvl) {
    this->level = lvl;
}

void GlobalVariant::setGameOver(const int& val) {
    this->is_gameover = val;
}

void GlobalVariant::setTotalBlock(const int& x, const int& y, const int& value) {
    this->total_block[y][x] = value;
}

void GlobalVariant::setTotalBlock(const int& x, const int& y, const int& value, const bool& isBitOrOperator) {
    this->total_block[y][x] |= value;
}

void GlobalVariant::callInitStage(const int& index, const int& speed, const int& stick_rate, const int& clear_line) {
    this->stage_data[index].init(speed, stick_rate, clear_line);
}

void GlobalVariant::init(const int& level, const int& lines, const int& ab_x, const int& ab_y) {
    this->level = level;
    this->lines = lines;
    this->ab_x = ab_x;
    this->ab_y = ab_y;

    this->block_shape = 0;
    this->block_angle = 0;
    this->block_x = 0;
    this->block_y = 0;
    this->next_block_shape = 0;
    this->score = 0;
    this->ctr = 0;
    initTotalBlock();
}
