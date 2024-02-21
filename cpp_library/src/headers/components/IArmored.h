#pragma once


class IArmored {
private:
    int armor;

protected:
    explicit IArmored(int armor);

public:
    void setArmor(int armorToSet);

    virtual int getArmor() const;

};
