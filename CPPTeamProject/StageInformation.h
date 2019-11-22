#pragma once
class StageInformation {
private:
    int	speed;	//���ڰ� �������� �ӵ��� ������
    int stick_rate;		//���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
    int clear_line;
public:
    void init(const int& speed, const int& stick_rate, const int& clear_line);
    int getSpeed() const;
    int getStickRate() const;
    int getClearLine() const;
    void setSpeed(const int& speed);
    void setStickRate(const int& stick_rate);
    void setClearLine(const int& clear_line);
};

