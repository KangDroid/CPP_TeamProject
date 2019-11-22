#pragma once
class StageInformation {
private:
    int	speed;	//���ڰ� �������� �ӵ��� ������
    int stick_rate;		//���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
    int clear_line;
public:
    void init(int speed, int stick_rate, int clear_line);
    int getSpeed() const;
    int getStickRate() const;
    int getClearLine() const;
    void setSpeed(int speed);
    void setStickRate(int stick_rate);
    void setClearLine(int clear_line);
};

