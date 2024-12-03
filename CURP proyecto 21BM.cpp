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

//Funcion para limpiar residuos que queden dentro de las varibles o linea de comando
void cleanInput(string printMessage = "") {
    cin.clear();//limpia la entrada       
    cin.ignore(1000, '\n');//ignora hasta mil errores  
    if (!printMessage.empty()) { 
        cout << printMessage;
    }
}
//Funcion para convertir una cadena de texto a mayusculas.
void convertirMayusculas(string& texto) {
    for (int i = 0; i < texto.size(); i++) {
        texto[i] = toupper(texto[i]);
    }
}
//Funcion para validar que la cadena de texto solo tenga letras y espacios.
bool esSoloLetrasYEspacios(const string& texto) {
    for (size_t i = 0; i < texto.length(); i++) {
    char c = texto[i];
    if (!isalpha(c) && c != ' ') {
        return false;
    }
}

    return true;
}
//Funcion para mandar a pedir un dato al usuario
void obtenerDato(string& dato, const string& mensaje, bool obligatorio = true) {
    do {
        cout << mensaje;
        getline(cin, dato);
		//Si el dato enviado esta vacio este lo vuelve a pedir ya que es obligatorio.
        if (dato.empty() && obligatorio) {
            cout << "Este campo es obligatorio. Intenta de nuevo.\n";
            continue;
        }
		//Llamamos a la funcion y si este regresa diferente de TRUE vuelve a pedir el dato
        if (!esSoloLetrasYEspacios(dato)) {
            cout << "Por favor, ingresa solo letras y espacios. Intenta de nuevo.\n";
            dato.clear();
        }
    } while (dato.empty() || !esSoloLetrasYEspacios(dato));
    
	//Al validar la entrada transforma la cadena a mayusculas
    convertirMayusculas(dato);
}
//Funcion para pedir los apellidos
void capturarApellidos(string& apellidoPaterno, string& apellidoMaterno) {
    string apellidos;
    do {
    	//Mandamos a pedir los apellidos
    cout << "\nIngresa tu(s) apellido(s)\n(Paterno y Materno separados por un espacio o presiona Enter si no tienes el otro): \nApellido(s): ";
        getline(cin, apellidos);

        // Validar si el usuario no ingresa nada
        if (apellidos.empty()) {
            apellidoPaterno = "X";
            apellidoMaterno = "X";
            return;
        }

        // Validar entrada valida
        if (!esSoloLetrasYEspacios(apellidos)) {
            cout << "Por favor, ingresa solo letras y espacios.\n";
            apellidos.clear();
        }
    } while (!esSoloLetrasYEspacios(apellidos));
	
    convertirMayusculas(apellidos);
	//declara true o false la variable si encuentra espacios vacios dentro del string apellidos.
    size_t espacio = apellidos.find(' ');
    //si dentro del string espacio no encontro lo que es un espacio ejecuta el if
    if (espacio != string::npos) {
        apellidoPaterno = apellidos.substr(0, espacio);
        apellidoMaterno = apellidos.substr(espacio + 1);
    } else {
        apellidoPaterno = apellidos;
        apellidoMaterno = "X";
    }
}
//Funcion para pedir el sexo
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
//Funcion para identificar si dentro del string hay un valor que no sea un numero
bool isDigits(const string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
//funcion para string a int
int stringToInt(const string& str) {
    return atoi(str.c_str());
}

//Funcion para pedir el cumplea;os 
bool ingBirthday(string& Fecha) {
    string birthday;
    cout << "\nIngresa la fecha en formato dd/mm/aaaa: ";
    cin >> birthday;

	//Buscamos dentro del string diagonales que son para reparar la fecha
    size_t primerSlash = birthday.find('/');
    size_t segundoSlash = birthday.find('/', primerSlash + 1);//buscamos la segunda diagonal

	//Si las varaibles no encontraron las dos diagonales vuelve a pedir la fecha 
    if (primerSlash == string::npos || segundoSlash == string::npos) {
        cleanInput("Formato incorrecto. Intenta de nuevo.\n");
        return false;
    }
	
	//Sacamos del string los valores para ingresarlos a una variable, desde un punto dado hasta el otro punto dado
    string day = birthday.substr(0, primerSlash);
    string month = birthday.substr(primerSlash + 1, segundoSlash - primerSlash - 1);
    string year = birthday.substr(segundoSlash + 1);

 	//Si cualquiera de las fechas no es una fecha de numeros este la volvera a pedir
    if (!isDigits(day) || !isDigits(month) || !isDigits(year)) {
        cleanInput("Formato incorrecto. Usa solo numeros.\n");
        return false;
    }

    int d = stringToInt(day);
    int m = stringToInt(month);
    int y = stringToInt(year);
	
	//valida que la fecha ingresada exista
    if (d < 1 || m < 1 || m > 12 || y < 1000 || y > 9999 || 
    (m == 2 && (d > 29 || (d == 29 && !(y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))))) || //mes de febrero
    (m == 4 || m == 6 || m == 9 || m == 11) && d > 30 || //meses de 30 dias
    (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d > 31) { //meses de 31 dias
    cleanInput("Fecha invalida. Intenta de nuevo.\n");
    return false;
	}

	//declaramos un onjeto
    stringstream ss;
    //indicamos que la longitud de cada variable debe ser de dos digitos si se ingresa un numero menor a 10 que ocupa dos posiciones se llena con un 0 para cumplir la condicion de 2 espacios.
    ss << setw(2) << setfill('0') << d 
       << setw(2) << setfill('0') << m 
       << y; 
	//guardamos el valor del objeto dentro de una variable
    Fecha = ss.str();
    return true;
}
//Funcion para hacer mayuscula eb caso de no funcionar el toupper
void toUpperCase(string& str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}
//Funcion para remover los acentos del string
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
//Funcion solo para mostrar los estados, (como si fuera una base de datos)
void mostrarEstadosValidos() {
    cout << "\n******************\n";
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

    cout << "******************\n";
}
//Funcion para validar el estado solicitado almacenando tambien la nomenclatura(como si fuera una DB)
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

	//Hacemos un ciclo para remover los acentos y hacemos mayuscula del estado solicitado para buscarlo con exactitud
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

//Funcion para obtener la primera vocal de un string
char obtenerPrimeraVocalInterna(const string& palabra) {
    for (size_t i = 1; i < palabra.length(); i++) { 
        char c = tolower(palabra[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return toupper(c);
        }
    }
    return 'X'; 
}
//Funcion para obtener la primera consonante de un string
char obtenerPrimeraConsonanteInterna(const string& palabra) {
    for (size_t i = 1; i < palabra.length(); i++) { 
        char c = tolower(palabra[i]);
        if (isalpha(c) && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
            return toupper(c);
        }
    }
    return 'X'; 
}

//Funcion para crear la curp
string generarCURP(const string& nombre, const string& apellidoPaterno, const string& apellidoMaterno,
                   const string& birthday, char sexo, const string& estado) {
    string curp;

   //Concatenamos la informacion recibida dentro de la variable
    curp += toupper(apellidoPaterno[0]);


    curp += obtenerPrimeraVocalInterna(apellidoPaterno);
	
	/*
	if (!apellidoPaterno.empty()) {
        curp += toupper(apellidoPaterno[0]);
    } else {
        curp += 'X'; 
    }
    */
    if (!apellidoMaterno.empty()) {
        curp += toupper(apellidoMaterno[0]);
    } else {
        curp += 'X'; 
    }
	
    size_t espacio = nombre.find(' ');
    
    string primerNombre;
	
	//Si esata almacenado un espacio dentro del nombre buscara todo el texto hasta el espacio, osea el segundo nombre
	if (espacio != string::npos) {
	    primerNombre = nombre.substr(0, espacio);
	} else {
	    primerNombre = nombre;
	}

    //Excepciones de nombres
    if ((primerNombre == "JOSE" || primerNombre == "MARIA" || primerNombre == "MA" || primerNombre == "J") && espacio != string::npos) {
        primerNombre = nombre.substr(espacio + 1);
    }
    curp += toupper(primerNombre[0]);
	
	//Extraemos las posiciones dentro del string de fecha de nacimiento
    curp += birthday.substr(6, 2); 
    curp += birthday.substr(2, 2); 
    curp += birthday.substr(0, 2); 


    curp += toupper(sexo);

 
    curp += estado;

    
    curp += obtenerPrimeraConsonanteInterna(apellidoPaterno);

	//Buscamos la primera consonante del apellido materno, en caso de estar vacio se sustituye por X
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

    // Obtener nombre(s)
    while (true) {
        obtenerDato(nombre, "Ingresa tu(s) nombre(s): ");
        if (esSoloLetrasYEspacios(nombre)) {
            break; // Nombre valido, salir del bucle
        } else {
            cout << "Por favor, ingresa solo letras y espacios. Intenta de nuevo.\n";
        }
    }

    // Obtener apellidos
    while (true) {
	    string apellidos;
	    cout << "\nIngresa tu(s) apellido(s)\n(Paterno y Materno separados por un espacio o presiona Enter si no tienes el otro): \nApellido(s): ";
	    getline(cin, apellidos);
	
	    // Verificar si la entrada esta vacia o contiene solo espacios
	    if (apellidos.empty() || apellidos.find_first_not_of(' ') == string::npos) {
	        apellidoPaterno = "X";
	        apellidoMaterno = "X";
	        break; // Salir del bucle si no se ingresa nada
	    }
	
	    // Validar que la entrada contenga solo letras y espacios
	    if (!esSoloLetrasYEspacios(apellidos)) {
	        cout << "Por favor, ingresa solo letras y espacios. Intenta de nuevo.\n";
	    } else {
	        // Convertir a mayusculas
	        convertirMayusculas(apellidos);
	
	        // Dividir los apellidos
	        size_t espacio = apellidos.find(' ');
	        if (espacio != string::npos) {
	            // Si encontramos un espacio, separamos los apellidos
	            apellidoPaterno = apellidos.substr(0, espacio);
	            apellidoMaterno = apellidos.substr(espacio + 1);
	        } else {
	            // Si no hay espacio, asignamos el apellido paterno y "X" para el materno
	            apellidoPaterno = apellidos;
	            apellidoMaterno = "X";
	        }
	        break; // Apellidos validos, salir del bucle
	    }
	}

    // Mostrar los datos capturados para confirmar
    cout << "\nDatos capturados para CURP:\n";
    cout << "Nombre(s): " << nombre << "\n";
    cout << "Apellido Paterno: " << apellidoPaterno << "\n";
    cout << "Apellido Materno: " << apellidoMaterno << "\n";

    // Capturar la fecha de nacimiento
    while (!ingBirthday(birthday)) {
        // Validar hasta obtener una fecha valida
    }
    cout << "Fecha almacenada: " << birthday << endl;

    // Capturar sexo
    ingSexo(sexo);

    // Mostrar lista de estados validos
    mostrarEstadosValidos();

    // Capturar estado de origen
    while (!obtenerEstado(estado)) {
        // Repetir hasta que sea valido
    }
    cout << "Estado v�lido ingresado: " << estado << endl;

    // Generar la CURP
    string curp = generarCURP(nombre, apellidoPaterno, apellidoMaterno, birthday, sexo, estado);

    // Mostrar CURP generada
    cout << "\nCURP generada: " << curp << endl;

    return 0;
}
