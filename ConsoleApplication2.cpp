#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

class Multipicaciopf{
 public:
    bitset<1> signonumero;
    bitset<8> expobnumero;
    bitset<23> significandonumero;

    void dectobin(float numero) {
        float xyz=numero;
        bitset<1> signodelnumero;
        if (numero >= 0) {
            signodelnumero[0] = 0;
        }
        else {
            signodelnumero[0] = 1;
        }


        if (numero < 0) {
            numero = -1 * numero;

        }if (numero >= 0) {
            numero = numero;
        }
        int numeropartentera = static_cast<int>(numero);
        float numero_dec = numero - static_cast<float>(numeropartentera);


        bitset<8> numeroentbin(numeropartentera);
        bitset<23> significando_temp;
        for (int i = 22; i >0; i--) {
            float y;
            numero_dec = round(numero_dec * 100.0) / 100.0;
            y = numero_dec * 2.0;
            if (y < 1.0) {
                significando_temp[i] = 0;
            }
            if (y >= 1.0) {
                y = y - 1.0;
                significando_temp[i] = 1;
            }

            numero_dec = y;
        }
        int posicionparteint=0;
        for (int i = 7; i >= 0; i--) {
            if (numeroentbin[i] == 0) {
                continue;
            }
            if (numeroentbin[i] == 1) {
                posicionparteint =  i;
                break;
            }
        }
        bitset<1> bitfinaltemp;
        for (int j = 0; j < posicionparteint ; j++) {
            bitfinaltemp[0] = numeroentbin[0];
            numeroentbin >>= 1;

            significando_temp >>= 1;
            significando_temp[22] = bitfinaltemp[0];
            ;
        }
        bitset<8> exponentfinal;
        if (posicionparteint == 0) {
            exponentfinal = 0;
        }
        else {
            exponentfinal = posicionparteint + 127;
        }

        if (xyz < 0) {
            cout << "El numero " << -1*numero << "   es en punto flotante: " << signodelnumero << " " << exponentfinal << " " << significando_temp << endl;
        }
        else {
            cout << "El numero " << numero << "   es en punto flotante: " << signodelnumero << " " << exponentfinal << " " << significando_temp << endl;
        }
        signonumero = signodelnumero;
        expobnumero = exponentfinal;
        significandonumero = significando_temp;

    }
     
};
bitset<8> suma_bin(bitset<8> x, bitset<8> y) {
    bitset<8> suma;
    bitset<8> carry(0);
    for (int i = 0; i < 8; i++) {
        suma[i] = (x[i] ^ y[i]) ^ carry[i];
        carry[i + 1] = (x[i] & y[i]) | (carry[i] & (x[i] ^ y[i]));
    }
    return suma;
}
void corrimiento_arit(bitset<8> a, bitset<8> x) {
    bitset<1> Q1(0);
    bitset<1> QA(0);
    bitset<1> Q0(x[0]);
    Q1 = Q0;
    QA[7] = a[0];
    for (int i = 0; i < 7; i++) {
        a[i + 1] = a[i];
    }
    a[0] = QA[0];

    for (int i = 0; i < 7; i++) {
        x[i + 1] = x[i];
    }
    x[0] = Q1[0];
}
void multiplicacionsinsigno(bitset<1> a, bitset<1> b, bitset<8> c, bitset<8> d, bitset<23> e, bitset<23> f, float x, float y) {
    bitset<1> signom(0);
    bitset<8> exponentem(0);
    bitset<23> significandom(0);
    signom = a ^ b;
    if ((a == 0 && c == 0 && e == 0) || (b == 0 && d == 0 && f == 0)) {
        signom = 0;
        exponentem = 0;
        significandom = 0;
        cout << "La multiplicacion es 0 o : " << signom<<" "<< exponentem<<" "<< significandom<< endl;
    }
    else {
        float sd = x * y;
        Multipicaciopf xx;
        xx.dectobin(sd);
        signom = xx.signonumero;
        exponentem = xx.expobnumero;
        significandom = xx.significandonumero;
        int m=c.to_ulong();
        m = m - 127;
        c = bitset<8>(m);
        //exponentem = suma_bin(c, d);

        cout << "La multiplicacion es  : " << signom << " " << exponentem << " " << significandom << endl;
    }

}
int main() {
    Multipicaciopf m;
    Multipicaciopf n;
    float x, y;
    cout << "Ingrese el primer numero: ";
    cin >> x;
    while (x < -255.0 || x>255.0) {
        cout << "Numero fuera del rango, ingrese de nuevo" << endl;
        cin >> x;
    }
    cout << "Ingrese el segundo numero: ";
    cin >> y;
    while (y < -255.0 || y>255.0) {
        cout << "Numero fuera del rango, ingrese de nuevo" << endl;
        cin >> y;
    }
    m.dectobin(x);
    n.dectobin(y);
    multiplicacionsinsigno(m.signonumero, n.signonumero, m.expobnumero, n.expobnumero, m.significandonumero, n.significandonumero, x ,y );


    return 0;
}