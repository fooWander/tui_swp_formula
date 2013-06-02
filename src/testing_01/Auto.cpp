
#include <iostream>

class Auto{
public:
    Auto(int tankgroesse, float tankinhalt, float verbrauch);

    void info()const;

    void fahren(int km);
    void tanken(float liter);

private:
    int   tankgroesse_;
    float tankinhalt_;
    float verbrauch_;
};

class Test : public Auto
{
public:
	Test(int tankgroesse);
	void out(int tankgroesse);
};

Test::out(int tankgroesse){
	std::cout << "Pupsgesicht " << tankgroesse << " Liter Treibstoff.\n";
}


Auto::Auto(int tankgroesse, float tankinhalt, float verbrauch):
    tankgroesse_(tankgroesse),
    tankinhalt_(tankinhalt),
    verbrauch_(verbrauch)
    {}

void Auto::info()const{
    std::cout << "In den Tank passen " << tankgroesse_ << " Liter Treibstoff.\n";
    std::cout << "Aktuell sind noch " << tankinhalt_ << " Liter im Tank.\n";
    std::cout << "Der Wagen verbraucht " << verbrauch_ << " Liter pro 100 km.\n";
    std::cout << std::endl;
}

void Auto::fahren(int km){
    std::cout << "Fahre " << km << " km.\n";
    tankinhalt_ -= verbrauch_*km/100;

    if(tankinhalt_ < 0.0f){
        tankinhalt_ = 0.0f;

        std::cout << "Mit dem aktuellen Tankinhalt schaffen Sie die Fahrt leider nicht.\n";
        std::cout << "Der Wagen ist unterwegs liegengeblieben, Zeit zu tanken!\n";
    }

    std::cout << std::endl;
}

void Auto::tanken( float liter ) {
    std::cout << "Tanke " << liter << " Liter.\n";
    tankinhalt_ += liter;

    if( tankinhalt_ > tankgroesse_ ) {
        tankinhalt_ = tankgroesse_;

        std::cout << "Nicht so übereifrig! Ihr Tank ist jetzt wieder voll.\n";
        std::cout << "Sie haben aber einiges daneben gegossen!\n";
    }

    std::cout << std::endl;
}


int main(){
	int x = 4;
	int y;
	std::cin >> x;
    Auto wagen(x, 60.0f, 5.7f);
    Test Klasse(y);

    Klasse.out(); 

    wagen.info();

    wagen.tanken(12.4f);
    wagen.info();

    wagen.fahren(230);
    wagen.info();

    wagen.fahren(12200);
    wagen.info();

    wagen.tanken(99.0f);
    wagen.info();
}
