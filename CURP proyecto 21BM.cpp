#include <iostream> // Para cout, cin
#include <cctype>   // Para isdigit(), isalpha()
#include <cstdlib>  // Para rand(), srand(), atoi()
#include <ctime>    // Para time()
#include <string>   // Para std::string
#include <conio.h>  // Para getch()
#include <iomanip>  // Para std::setw, std::setfill
#include <sstream>  // Para std::stringstream
#include <algorithm>  // Para std::sort, std::find, std::unique

using namespace std;


void cleanInput(string printMessage = "") {
    cin.clear();           
    cin.ignore(1000, '\n');   
    if (!printMessage.empty()) { 
        cout << printMessage;
    }
}

void convertirMayusculas(string& texto) {
    for (int i = 0; i < texto.size(); i++) {
        texto[i] = toupper(texto[i]);
    }
}

bool esSoloLetrasYEspacios(const string& texto); // Declaración


bool esSoloLetrasYEspacios(const string& texto) {
    for (size_t i = 0; i < texto.length(); i++) {
    char c = texto[i];
    if (!isalpha(c) && c != ' ') {
        return false;
    }
}

    return true;
}

void obtenerDato(string& dato, const string& mensaje, bool obligatorio = true) {
    do {
        cout << mensaje;
        getline(cin, dato);

        if (dato.empty() && obligatorio) {
            cout << "Este campo es obligatorio. Intenta de nuevo.\n";
            continue;
        }

        if (!esSoloLetrasYEspacios(dato)) {
            cout << "Por favor, ingresa solo letras y espacios. Intenta de nuevo.\n";
            dato.clear();
        }
    } while (dato.empty() || !esSoloLetrasYEspacios(dato));

    convertirMayusculas(dato);
}

void capturarApellidos(string& apellidoPaterno, string& apellidoMaterno) {
    string apellidos;
    do {
        cout << "\nIngresa tu(s) apellido(s)\n(Paterno y Materno separados por un espacio o presiona Enter si no tienes el otro): \n";
        getline(cin, apellidos);

        if (!esSoloLetrasYEspacios(apellidos)) {
            cout << "Por favor, ingresa solo letras y espacios.\n";
            apellidos.clear();
        }
    } while (apellidos.empty() || !esSoloLetrasYEspacios(apellidos));

    convertirMayusculas(apellidos);

    size_t espacio = apellidos.find(' ');
    if (espacio != string::npos) {
        apellidoPaterno = apellidos.substr(0, espacio);
        apellidoMaterno = apellidos.substr(espacio + 1);
    } else {
        apellidoPaterno = apellidos;
        apellidoMaterno = "X";
    }
}



bool ingSexo(char& sexo) {
    cout << "Sexo (H/M): ";
    while (true) {
        sexo = getch(); 
        cout << sexo;  
        
        if (sexo == 'h' || sexo == 'H' || sexo == 'm' || sexo == 'M') {
            cleanInput(); 
            return true;
        } else {
            cleanInput(" Ingresa un sexo valido (H/M): ");
        }
    }
}




bool isDigits(const string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


int stringToInt(const string& str) {
    return atoi(str.c_str());
}


bool ingBirthday(string& Fecha) {
    string birthday;
    cout << "\nIngresa la fecha en formato dd/mm/aaaa: ";
    cin >> birthday;

    
    size_t primerSlash = birthday.find('/');
    size_t segundoSlash = birthday.find('/', primerSlash + 1);

    if (primerSlash == string::npos || segundoSlash == string::npos) {
        cleanInput("Formato incorrecto. Intenta de nuevo.\n");
        return false;
    }

    string day = birthday.substr(0, primerSlash);
    string month = birthday.substr(primerSlash + 1, segundoSlash - primerSlash - 1);
    string year = birthday.substr(segundoSlash + 1);

 
    if (!isDigits(day) || !isDigits(month) || !isDigits(year)) {
        cleanInput("Formato incorrecto. Usa solo numeros.\n");
        return false;
    }

    int d = stringToInt(day);
    int m = stringToInt(month);
    int y = stringToInt(year);

    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1000 || y > 9999) {
        cleanInput("Fecha invalida. Intenta de nuevo.\n");
        return false;
    }

    stringstream ss;
    ss << setw(2) << setfill('0') << d 
       << setw(2) << setfill('0') << m 
       << y; 

    Fecha = ss.str();
    return true;
}

void toUpperCase(string& str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

string removeAccents(const string& str) {
    string result;
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
  
       if (c == 'á' || c == 'à' || c == 'ä' || c == 'â') c = 'a';
        else if (c == 'é' || c == 'è' || c == 'ë' || c == 'ê') c = 'e';
        else if (c == 'í' || c == 'ì' || c == 'ï' || c == 'î') c = 'i';
        else if (c == 'ó' || c == 'ò' || c == 'ö' || c == 'ô') c = 'o';
        else if (c == 'ú' || c == 'ù' || c == 'ü' || c == 'û') c = 'u';
        else if (c == 'ñ') c = 'n';
        result += c;
    }
    return result;
}

void mostrarEstadosValidos() {
    cout << "\n**************************************************\n";
    cout << "              ESTADOS VALIDOS DE MEXICO\n";
    cout << "1. Aguascalientes (AS)\n";
    cout << "2. Baja California (BC)\n";
    cout << "3. Baja California Sur (BS)\n";
    cout << "4. Campeche (CC)\n";
    cout << "5. Chiapas (CS)\n";
    cout << "6. Chihuahua (CH)\n";
    cout << "7. Coahuila (CL)\n";
    cout << "8. Colima (CM)\n";
    cout << "9. Durango (DG)\n";
    cout << "10. Guanajuato (GT)\n";
    cout << "11. Guerrero (GR)\n";
    cout << "12. Hidalgo (HG)\n";
    cout << "13. Jalisco (JC)\n";
    cout << "14. Mexico (MC)\n";
    cout << "15. Michoacan (MN)\n";
    cout << "16. Morelos (MS)\n";
    cout << "17. Nayarit (NT)\n";
    cout << "18. Nuevo Leon (NL)\n";
    cout << "19. Oaxaca (OC)\n";
    cout << "20. Puebla (PL)\n";
    cout << "21. Queretaro (QT)\n";
    cout << "22. Quintana Roo (QR)\n";
    cout << "23. San Luis Potosi (SP)\n";
    cout << "24. Sinaloa (SL)\n";
    cout << "25. Sonora (SR)\n";
    cout << "26. Tabasco (TC)\n";
    cout << "27. Tamaulipas (TS)\n";
    cout << "28. Tlaxcala (TL)\n";
    cout << "29. Veracruz (VZ)\n";
    cout << "30. Yucatan (YN)\n";
    cout << "31. Zacatecas (ZS)\n";
    cout << "32. Ciudad de Mexico (DF)\n";
    cout << "33. Extranjero (NE)\n";

    cout << "**************************************************\n";
}

bool obtenerEstado(string& estado) {

    string estados[][3] = {
        {"Aguascalientes", "AS", "1"}, {"Baja California", "BC", "2"}, {"Baja California Sur", "BS", "3"},
        {"Campeche", "CC", "4"}, {"Chiapas", "CS", "5"}, {"Chihuahua", "CH", "6"},
        {"Coahuila", "CL", "7"}, {"Colima", "CM", "8"}, {"Durango", "DG", "9"},
        {"Guanajuato", "GT", "10"}, {"Guerrero", "GR", "11"}, {"Hidalgo", "HG", "12"},
        {"Jalisco", "JC", "13"}, {"Mexico", "MC", "14"}, {"Michoacan", "MN", "15"},
        {"Morelos", "MS", "16"}, {"Nayarit", "NT", "17"}, {"Nuevo Leon", "NL", "18"},
        {"Oaxaca", "OC", "19"}, {"Puebla", "PL", "20"}, {"Queretaro", "QT", "21"},
        {"Quintana Roo", "QR", "22"}, {"San Luis Potosi", "SP", "23"}, {"Sinaloa", "SL", "24"},
        {"Sonora", "SR", "25"}, {"Tabasco", "TC", "26"}, {"Tamaulipas", "TS", "27"},
        {"Tlaxcala", "TL", "28"}, {"Veracruz", "VZ", "29"}, {"Yucatan", "YN", "30"},
        {"Zacatecas", "ZS", "31"}, {"Ciudad de Mexico", "DF", "32"}, {"Extranjero", "NE", "33"}
    };
    
    string input;
    cout << "Ingresa tu estado de origen (por nombre completo, abreviatura o numero): ";
    getline(cin, input);
  
    input = removeAccents(input);
    toUpperCase(input);


    for (int i = 0; i < 33; ++i) {

        string estadoValidado = removeAccents(estados[i][0]);
        toUpperCase(estadoValidado);

        if (input == estadoValidado || input == estados[i][1] || input == estados[i][2]) {
            estado = estados[i][1]; 
            return true;
        }
    }


    cout << "Estado no valido. Intenta de nuevo.\n";
    return false;
}


char obtenerPrimeraVocalInterna(const string& palabra) {
    for (size_t i = 1; i < palabra.length(); i++) { 
        char c = tolower(palabra[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return toupper(c);
        }
    }
    return 'X'; 
}

char obtenerPrimeraConsonanteInterna(const string& palabra) {
    for (size_t i = 1; i < palabra.length(); i++) { 
        char c = tolower(palabra[i]);
        if (isalpha(c) && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
            return toupper(c);
        }
    }
    return 'X'; 
}


string generarCURP(const string& nombre, const string& apellidoPaterno, const string& apellidoMaterno,
                   const string& birthday, char sexo, const string& estado) {
    string curp;

   
    curp += toupper(apellidoPaterno[0]);


    curp += obtenerPrimeraVocalInterna(apellidoPaterno);


    if (!apellidoMaterno.empty()) {
        curp += toupper(apellidoMaterno[0]);
    } else {
        curp += 'X'; 
    }

    size_t espacio = nombre.find(' ');
    
    string primerNombre;

	if (espacio != string::npos) {
	    primerNombre = nombre.substr(0, espacio);
	} else {
	    primerNombre = nombre;
	}

    
    if ((primerNombre == "JOSE" || primerNombre == "MARIA" || primerNombre == "MA" || primerNombre == "J") && espacio != string::npos) {
        primerNombre = nombre.substr(espacio + 1);
    }
    curp += toupper(primerNombre[0]);

    curp += birthday.substr(6, 2); 
    curp += birthday.substr(2, 2); 
    curp += birthday.substr(0, 2); 


    curp += toupper(sexo);

 
    curp += estado;

    
    curp += obtenerPrimeraConsonanteInterna(apellidoPaterno);

    if (!apellidoMaterno.empty()) {
        curp += obtenerPrimeraConsonanteInterna(apellidoMaterno);
    } else {
        curp += 'X';
    }

    
    curp += obtenerPrimeraConsonanteInterna(primerNombre);

    return curp;
}

 int main() {
    char sexo;
    string birthday, nombre, apellidoPaterno, apellidoMaterno, estado;

    cout << "Conseguir CURP: " << endl;

    
    while (true) {
        obtenerDato(nombre, "Ingresa tu(s) nombre(s): ");
        if (esSoloLetrasYEspacios(nombre)) {
            break; 
        } else {
            cout << "Por favor, ingresa solo letras y espacios. Intenta de nuevo.\n";
        }
    }

    // Obtener apellidos
    while (true) {
        string apellidos;
        cout << "\nIngresa tu(s) apellido(s)\n(Paterno y Materno separados por un espacio o presiona Enter si no tienes el otro): ";
        getline(cin, apellidos);

        if (esSoloLetrasYEspacios(apellidos)) {
            convertirMayusculas(apellidos);

            // Dividir los apellidos
            size_t espacio = apellidos.find(' ');
            if (espacio != string::npos) {
                apellidoPaterno = apellidos.substr(0, espacio);
                apellidoMaterno = apellidos.substr(espacio + 1);
            } else {
                apellidoPaterno = apellidos;
                apellidoMaterno = "X"; // Asignar "X" si no hay apellido materno
            }
            break; 
        } else {
            cout << "Por favor, ingresa solo letras y espacios. Intenta de nuevo.\n";
        }
    }

   
    cout << "\nDatos capturados para CURP:\n";
    cout << "Nombre(s): " << nombre << "\n";
    cout << "Apellido Paterno: " << apellidoPaterno << "\n";
    cout << "Apellido Materno: " << apellidoMaterno << "\n";

  
    while (!ingBirthday(birthday)) {
        
    }
    cout << "Fecha almacenada: " << birthday << endl;

    
    ingSexo(sexo);

    
    mostrarEstadosValidos();

 
    while (!obtenerEstado(estado)) {
       
    }
    cout << "Estado válido ingresado: " << estado << endl;

  
    string curp = generarCURP(nombre, apellidoPaterno, apellidoMaterno, birthday, sexo, estado);

    cout << "\nCURP generada: " << curp << endl;

    return 0;
}

