/*
 * Programa demostrativo de manipulación procesamiento de imágenes BMP en C++ usando Qt.
 *
 * Descripción:
 * Este programa realiza las siguientes tareas:
 * 1. Carga una imagen BMP desde un archivo (formato RGB sin usar estructuras ni STL).
 * 2. Modifica los valores RGB de los píxeles asignando un degradado artificial basado en su posición.
 * 3. Exporta la imagen modificada a un nuevo archivo BMP.
 * 4. Carga un archivo de texto que contiene una semilla (offset) y los resultados del enmascaramiento
 *    aplicados a una versión transformada de la imagen, en forma de tripletas RGB.
 * 5. Muestra en consola los valores cargados desde el archivo de enmascaramiento.
 * 6. Gestiona la memoria dinámicamente, liberando los recursos utilizados.
 *
 * Entradas:
 * - Archivo de imagen BMP de entrada ("I_O.bmp").
 * - Archivo de salida para guardar la imagen modificada ("I_D.bmp").
 * - Archivo de texto ("M1.txt") que contiene:
 *     • Una línea con la semilla inicial (offset).
 *     • Varias líneas con tripletas RGB resultantes del enmascaramiento.
 *
 * Salidas:
 * - Imagen BMP modificada ("I_D.bmp").
 * - Datos RGB leídos desde el archivo de enmascaramiento impresos por consola.
 *
 * Requiere:
 * - Librerías Qt para manejo de imágenes (QImage, QString).
 * - No utiliza estructuras ni STL. Solo arreglos dinámicos y memoria básica de C++.
 *
 * Autores: Augusto Salazar Y Aníbal Guerra
 * Fecha: 06/04/2025
 * Asistencia de ChatGPT para mejorar la forma y presentación del código fuente
 */

#include <fstream>
#include <iostream>
#include <QCoreApplication>
#include <QImage>

using namespace std;

/* ***************************** Declaración de funnciones ***************************** */

unsigned char* loadPixels(QString input, int &width, int &height);
bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

unsigned char desplazamientoIzq(unsigned char Id, int n);
unsigned char desplazamientoDer(unsigned char Id, int n);
unsigned char rotacionIzq(unsigned char Id, int n);
unsigned char rotacionDer(unsigned char Id, int n);
unsigned char operacionXor(unsigned char Id, unsigned char IM);
unsigned char* revertirEnmas(unsigned int* Id, unsigned char* M, int i, int j);
void enmascaramiento(unsigned char* Id, int wId, int hId, unsigned char* M, int wM, int hM, int s);


/* ******************************** Función Principal ************************************ */

int main()
{
    /* Definición de rutas de archivo de entrada (imagen original), salida (imagen modificada), de la imagen máscara y de la máscara
    QString archivoEntrada = "I_O.bmp";
    QString archivoSalida = "I_D.bmp";
    QString Imascara = "I_M.bmp";
    QString mascara = "M.bmp";
    QString etapa = "P2.bmp";


    // Variables para almacenar las dimensiones de la imagen, de la imagen máscara y de la máscara
    int height = 0;
    int width = 0;

    int hIm=0;
    int wIm=0;

    int hm=0;
    int wm=0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto
    //unsigned char *pixelData = loadPixels(archivoEntrada, width, height);
    unsigned char *pixelData = loadPixels(etapa, width, height);

    // Carga la imagen máscara BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *ImaskData = loadPixels(Imascara, wIm, hIm);

    // Carga la máscara BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *maskData = loadPixels(mascara, wm, hm);

    // Asegurarse que las dimensiones coincidan
    if (width != wIm || height != hIm) {
        cout << "Las imagenes no tienen el mismo tamaño." << endl;
        return -1; //convención para indicar que hay un error
    }*/

    /*Simula una modificación de la imagen asignando valores RGB incrementales
    // (Esto es solo un ejemplo de manipulación artificial)
    for (int i = 0; i < width * height * 3; i += 3) {
        pixelData[i] = i;     // Canal rojo
        pixelData[i + 1] = i; // Canal verde
        pixelData[i + 2] = i; // Canal azul
    }*/

    /* Simula operaciones a nivel de bits
    int totalSize = width * height * 3;
    for (int i = 0; i < totalSize; i++) {
        // XOR con la imagen máscara
        pixelData[i] = operacionXor(pixelData[i], ImaskData[i]);

        // Rotar a la derecha 3 bits
        pixelData[i] = rotacionIzq(pixelData[i], 7);

        // Desplazamiento opcional (ejemplo: desplazar 1 bit a la izquierda)
        pixelData[i] = desplazamientoIzq(pixelData[i],3); // cuidado: puede perder información
    }*/

    // Exporta la imagen modificada a un nuevo archivo BMP
    //bool exportI = exportImage(pixelData, width, height, archivoSalida);

    // Muestra si la exportación fue exitosa (true o false)
    //cout << exportI << endl;

    /* Libera la memoria usada para los píxeles
    delete[] pixelData;
    pixelData = nullptr;*/

    /* Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed = 0;
    int n_pixels = 0;

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData = loadSeedMasking("M2.txt", seed, n_pixels);

    // Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    for (int i = 0; i < n_pixels * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData[i] << ", "
             << maskingData[i + 1] << ", "
             << maskingData[i + 2] << ")" << endl;
    }

    // Revertir enmascaramiento
    unsigned char *original=revertirEnmas(maskingData,maskData,hm,wm);

    for (int i=0; i <hm*wm*3; i++) {

        if(i+seed>height*width){
            cout<<endl<<"La semilla es muy grande posible desbordamiento"<<endl;
            break;
        }
        else{
            pixelData[i+seed] = original[i];
        }

    }

    // Exporta la imagen modificada a un nuevo archivo BMP
    bool exportI = exportImage(pixelData, width, height, archivoSalida);

    // Muestra si la exportación fue exitosa (true o false)
    cout << exportI << endl;

    // Libera la memoria usada para los datos de enmascaramiento
    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }

    delete[] pixelData;
    pixelData = nullptr;*/



    /* ******************************** Set de prueba para el caso 1 ****************************** */

    /* Segunda etapa

    //QString archivoEntrada = "I_O.bmp";
    QString archivoSalida = "Final.bmp";
    QString Imascara = "I_M.bmp";
    QString mascara = "M.bmp";
    QString etapa2 = "P2.bmp";

    // Variables para almacenar las dimensiones de la imagen, de la imagen máscara y de la máscara
    int height = 0;
    int width = 0;

    int hIm=0;
    int wIm=0;

    int hm=0;
    int wm=0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto
    //unsigned char *pixelData = loadPixels(archivoEntrada, width, height);
    unsigned char *pixelData = loadPixels(etapa2, width, height);

    // Carga la imagen máscara BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *ImaskData = loadPixels(Imascara, wIm, hIm);

    // Carga la máscara BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *maskData = loadPixels(mascara, wm, hm);

    // Asegurarse que las dimensiones coincidan
    if (width != wIm || height != hIm) {
        cout << "Las imágenes no tienen el mismo tamaño." << endl;
        return -1; //convención para indicar que hay un error
    }

    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed = 0;
    int n_pixels = 0;

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData = loadSeedMasking("M2.txt", seed, n_pixels);

    // Revertir enmascaramiento
    unsigned char *original=revertirEnmas(maskingData,maskData,hm,wm);

    for (int i=0; i <hm*wm*3; i++) {

        if(i+seed>height*width){
            cout<<endl<<"La semilla es muy grande posible desbordamiento"<<endl;
            break;
        }
        else{
            pixelData[i+seed] = original[i];
        }

    }

    //  Simula operaciones a nivel de bits
    int totalSize = width * height * 3;

    for (int i = 0; i < totalSize; i++) {
        // XOR con la imagen máscara
        //pixelData[i] = operacionXor(pixelData[i], ImaskData[i]);

        // Rotar a la derecha 3 bits
        pixelData[i] = rotacionIzq(pixelData[i], 3);

        // Desplazamiento opcional (ejemplo: desplazar 1 bit a la izquierda)
        //pixelData[i] = desplazamientoIzq(pixelData[i],3); // cuidado: puede perder información
    }

    // Exporta la imagen modificada a un nuevo archivo BMP
    // bool exportI = exportImage(pixelData, width, height, archivoSalida);

    // Muestra si la exportación fue exitosa (true o false)
    // cout << exportI << endl;


    // Primera etapa

    //QString archivoEntrada = "I_O.bmp";
    //QString Salida = "Etapa1.bmp";
    //QString Imascara = "I_M.bmp";
    //QString mascara = "M.bmp";
    //QString etapa1 = "Etapa2.bmp";

    //unsigned char *pixelData1 = loadPixels(etapa1, width, height);


    //enmascaramiento(pixelData, width, height, maskData, wm, hm, seed);


    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed1 = 0;
    int n_pixels1 = 0;

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData1 = loadSeedMasking("M1.txt", seed1, n_pixels1);

    enmascaramiento(pixelData, width, height, maskData, wm, hm, seed1);

    int validacion=false;

    unsigned int *validacionData = loadSeedMasking("Validacion.txt", seed1, n_pixels1);

    for (int k = 0; k < n_pixels1*3; k++) {

        if (validacionData[k]!=maskingData1[k]){
            validacion=false;
            *validacData=*pixelData;
            //cout<<endl<<"No es operacion XOR"<<endl;
            break;

        }

        else{

            validacion=true;
            //cout<<endl<<"Es operacion XOR"<<endl;

        }

        cout<<endl<<validacion<<endl;

    }



    // Revertir enmascaramiento
    unsigned char *original1=revertirEnmas(maskingData1,maskData,hm,wm);

    for (int i=0; i <hm*wm*3; i++) {

        if(i+seed>height*width){
            cout<<endl<<"La semilla es muy grande posible desbordamiento"<<endl;
            break;
        }
        else{
            pixelData[i+seed1] = original1[i];
        }

    }

    //  Simula operaciones a nivel de bits
    int totalSize1 = width * height * 3;
    for (int i = 0; i < totalSize; i++) {
        // XOR con la imagen máscara
        pixelData[i] = operacionXor(pixelData[i], ImaskData[i]);

        // Rotar a la derecha 3 bits
        //pixelData[i] = rotacionIzq(pixelData[i], 3);

        // Desplazamiento opcional (ejemplo: desplazar 1 bit a la izquierda)
        //pixelData[i] = desplazamientoIzq(pixelData[i],3); // cuidado: puede perder información
    }

    // Exporta la imagen modificada a un nuevo archivo BMP
    bool exportI = exportImage(pixelData, width, height, archivoSalida);

    // Muestra si la exportación fue exitosa (true o false)
    cout << exportI << endl;

    // Libera la memoria usada para los datos de enmascaramiento
    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }

    delete[] pixelData;
    pixelData = nullptr;*/




    /* ******************************** Set de prueba para el caso 2 **************************** */


    // Etapa 6

    // Definición de rutas de archivo de entrada (imagen original), salida (imagen modificada), de la imagen máscara y de la máscara
    QString archivoEntrada = "P6.bmp";
    QString archivoSalida = "Etapa6.bmp";
    QString Imascara = "I_M.bmp";
    QString mascara = "M.bmp";
    //QString etapa = "P2.bmp";


    // Variables para almacenar las dimensiones de la imagen, de la imagen máscara y de la máscara
    int height = 0;
    int width = 0;

    int hIm=0;
    int wIm=0;

    int hm=0;
    int wm=0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto
    //unsigned char *pixelData = loadPixels(archivoEntrada, width, height);
    unsigned char *pixelData = loadPixels(archivoEntrada, width, height);

    // Carga la imagen máscara BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *ImaskData = loadPixels(Imascara, wIm, hIm);

    // Carga la máscara BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *maskData = loadPixels(mascara, wm, hm);

    // Asegurarse que las dimensiones coincidan
    if (width != wIm || height != hIm) {
        cout << "Las imagenes no tienen el mismo tamaño." << endl;
        return -1; //convención para indicar que hay un error
    }

    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed = 0;
    int n_pixels = 0;

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData = loadSeedMasking("M6.txt", seed, n_pixels);

    /* Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    for (int i = 0; i < n_pixels * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData[i] << ", "
             << maskingData[i + 1] << ", "
             << maskingData[i + 2] << ")" << endl;
    }*/

    // Revertir enmascaramiento
    unsigned char *original=revertirEnmas(maskingData,maskData,hm,wm);

    for (int i=0; i <hm*wm*3; i++) {

        if(i+seed>height*width){
            cout<<endl<<"La semilla es muy grande posible desbordamiento"<<endl;
            break;
        }
        else{
            pixelData[i+seed] = original[i];
        }

    }

    // Exporta la imagen modificada a un nuevo archivo BMP
    bool exportI = exportImage(pixelData, width, height, archivoSalida);

    // Muestra si la exportación fue exitosa (true o false)
    cout << exportI << endl;

    QString archivodeSalida = "Etapa6.bmp";

    int hvalidacion = 0;
    int wvalidacion = 0;

    unsigned char *validacData = loadPixels(archivodeSalida, wvalidacion, hvalidacion);

    // Algoritmo para identificar operaciones a nivel de bit y verificar enmascaramiento

    bool validacion=true;
    int totalSize = width*height*3;

    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed1 = 0;
    int n_pixels1 = 0;

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData1 = loadSeedMasking("M5.txt", seed1, n_pixels1);



    /* *************************** Operación XOR ***************************** */

    do{

    for (int i = 0; i < totalSize; i++) {

        //XOR con la imagen máscara
        validacData[i] = operacionXor(validacData[i], ImaskData[i]);
        //validacData[i] = operacionXor(validacData[i], ImaskData[i]);

    }

    enmascaramiento(validacData, wvalidacion, hvalidacion, maskData, wm,hm,seed1);

    int n_pixels2=0;

    unsigned int *validacionData = loadSeedMasking("Validacion.txt", seed1, n_pixels2);

    if (n_pixels2!=n_pixels1){

        cout<<endl<<"No es operacion XOR"<<endl;
        validacion=false;
    }

    else{

        /* Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
            for (int i = 0; i < n_pixels2 * 3; i += 3) {
                cout << "Pixel " << i / 3 << ": ("
                     << validacionData[i] << ", "
                     << validacionData[i + 1] << ", "
                     << validacionData[i + 2] << ")" << endl;
            }*/

        for (int k = 0; k < n_pixels2*3; k++) {

            if (validacionData[k]!=maskingData1[k]){
                validacion=false;
                //*validacData=*pixelData;
                //cout<<endl<<"No es operacion XOR"<<endl;
                break;

            }

            else{

                validacion=true;
                //cout<<endl<<"Es operacion XOR"<<endl;

            }

        }

    }

    if (validacion==true){

         cout<<endl<<"Es operacion XOR"<<endl;
         break;

    }

    else{

        cout<<endl<<"No es operacion XOR"<<endl;

        for (int i = 0; i < totalSize; i++) {

            //XOR con la imagen máscara
            validacData[i] = operacionXor(validacData[i], ImaskData[i]);
            //validacData[i] = operacionXor(validacData[i], ImaskData[i]);

        }

    }





    /* ***************************** Rotación a la derecha ******************************* */



    for (int j=1;j<9;j++){

        for (int i = 0; i < totalSize; i++) {

            // Original rotar a la derecha
            validacData[i] = rotacionIzq(validacData[i], j);
            //validacData[i] = rotacionDer(validacData[i], j);
        }

        enmascaramiento(validacData, wvalidacion, hvalidacion, maskData, wm,hm,seed1);

        int n_pixels2=0;

        unsigned int *validacionData = loadSeedMasking("Validacion.txt", seed1, n_pixels2);

        if (n_pixels2!=n_pixels1){

            cout<<endl<<"No es operacion rotacion a la derecha de "<<j<<"bits"<<endl;
            validacion=false;
        }

        else{

            /* Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
            for (int i = 0; i < n_pixels2 * 3; i += 3) {
                cout << "Pixel " << i / 3 << ": ("
                     << validacionData[i] << ", "
                     << validacionData[i + 1] << ", "
                     << validacionData[i + 2] << ")" << endl;
            }*/

            for (int k = 0; k < n_pixels2*3; k++) {

                if (validacionData[k]!=maskingData1[k]){
                    validacion=false;
                    //*validacData=*pixelData;
                    //cout<<endl<<"No es operacion XOR"<<endl;
                    break;

                }

                else{

                    validacion=true;
                    //cout<<endl<<"Es operacion XOR"<<endl;

                }

            }


        }

        if (validacion==true){

            cout<<endl<<"Es operacion rotacion a la derecha de "<<j<<"bits"<<endl;

            break;

        }

        else{

            cout<<endl<<"No es operacion rotacion a la derecha de "<<j<<"bits"<<endl;

            for (int i = 0; i < totalSize; i++) {

                // Original rotar a la derecha
                validacData[i] = rotacionDer(validacData[i], j);
                //validacData[i] = rotacionDer(validacData[i], j);
            }



        }


        cout<<endl<<"Bandera con j"<<j<<" "<<validacion<<endl;

    }

    if (validacion==true){
        break;
    }



    /* ******************************** Rotación a la iquierda ************************ */



    for (int j=1;j<9;j++){

        for (int i = 0; i < totalSize; i++) {

            // Original rotar a la izquierda
            validacData[i] = rotacionDer(validacData[i], j);
            //validacData[i] = rotacionDer(validacData[i], j);
        }

        enmascaramiento(validacData, wvalidacion, hvalidacion, maskData, wm,hm,seed1);

        int n_pixels2=0;

        unsigned int *validacionData = loadSeedMasking("Validacion.txt", seed1, n_pixels2);

        if (n_pixels2!=n_pixels1){

            cout<<endl<<"No es operacion rotacion a la izquierda de "<<j<<"bits"<<endl;
            validacion=false;
        }

        else{

            /* Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
            for (int i = 0; i < n_pixels2 * 3; i += 3) {
                cout << "Pixel " << i / 3 << ": ("
                     << validacionData[i] << ", "
                     << validacionData[i + 1] << ", "
                     << validacionData[i + 2] << ")" << endl;
            }*/

            for (int k = 0; k < n_pixels2*3; k++) {

                if (validacionData[k]!=maskingData1[k]){
                    validacion=false;
                    //*validacData=*pixelData;
                    //cout<<endl<<"No es operacion XOR"<<endl;
                    break;

                }

                else{

                    validacion=true;
                    //cout<<endl<<"Es operacion XOR"<<endl;

                }

            }


        }

        if (validacion==true){

            cout<<endl<<"Es operacion rotacion a la izquierda de "<<j<<"bits"<<endl;

            break;

        }

        else{

            cout<<endl<<"No es operacion rotacion a la izquierda de "<<j<<"bits"<<endl;

            for (int i = 0; i < totalSize; i++) {

                // Original rotar a la derecha
                validacData[i] = rotacionIzq(validacData[i], j);
                //validacData[i] = rotacionDer(validacData[i], j);
            }



        }


        cout<<endl<<"Bandera con j"<<j<<" "<<validacion<<endl;

    }

    if (validacion==true){
        break;
    }




    // Desplazamiento a la derecha



    for (int j=1;j<9;j++){

        for (int i = 0; i < totalSize; i++) {

            // Original rotar a la derecha
            validacData[i] = desplazamientoIzq(validacData[i], j);
            //validacData[i] = rotacionDer(validacData[i], j);
        }

        enmascaramiento(validacData, wvalidacion, hvalidacion, maskData, wm,hm,seed1);

        int n_pixels2=0;

        unsigned int *validacionData = loadSeedMasking("Validacion.txt", seed1, n_pixels2);

        if (n_pixels2!=n_pixels1){

            cout<<endl<<"No es operacion desplazamiento a la derecha de "<<j<<"bits"<<endl;
            validacion=false;
        }

        else{

            /* Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
            for (int i = 0; i < n_pixels2 * 3; i += 3) {
                cout << "Pixel " << i / 3 << ": ("
                     << validacionData[i] << ", "
                     << validacionData[i + 1] << ", "
                     << validacionData[i + 2] << ")" << endl;
            }*/

            for (int k = 0; k < n_pixels2*3; k++) {

                if (validacionData[k]!=maskingData1[k]){
                    validacion=false;
                    //*validacData=*pixelData;
                    //cout<<endl<<"No es operacion XOR"<<endl;
                    break;

                }

                else{

                    validacion=true;
                    //cout<<endl<<"Es operacion XOR"<<endl;

                }

            }


        }

        if (validacion==true){

            cout<<endl<<"Es operacion desplazamiento a la derecha de "<<j<<"bits"<<endl;

            break;

        }

        else{

            cout<<endl<<"No es operacion desplazamiento a la derecha de "<<j<<"bits"<<endl;

            for (int i = 0; i < totalSize; i++) {

                // Original rotar a la derecha
                validacData[i] = desplazamientoDer(validacData[i], j);
                //validacData[i] = rotacionDer(validacData[i], j);
            }



        }


        cout<<endl<<"Bandera con j"<<j<<" "<<validacion<<endl;

    }

    if (validacion==true){
        break;
    }




    // Desplazamiento a la iquierda



    for (int j=1;j<9;j++){

        for (int i = 0; i < totalSize; i++) {

            // Original rotar a la izquierda
            validacData[i] = desplazamientoDer(validacData[i], j);
            //validacData[i] = rotacionDer(validacData[i], j);
        }

        enmascaramiento(validacData, wvalidacion, hvalidacion, maskData, wm,hm,seed1);

        int n_pixels2=0;

        unsigned int *validacionData = loadSeedMasking("Validacion.txt", seed1, n_pixels2);

        if (n_pixels2!=n_pixels1){

            cout<<endl<<"No es operacion desplazamiento a la izquierda de "<<j<<"bits"<<endl;
            validacion=false;
        }

        else{

            /* Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
            for (int i = 0; i < n_pixels2 * 3; i += 3) {
                cout << "Pixel " << i / 3 << ": ("
                     << validacionData[i] << ", "
                     << validacionData[i + 1] << ", "
                     << validacionData[i + 2] << ")" << endl;
            }*/

            for (int k = 0; k < n_pixels2*3; k++) {

                if (validacionData[k]!=maskingData1[k]){
                    validacion=false;
                    //*validacData=*pixelData;
                    //cout<<endl<<"No es operacion XOR"<<endl;
                    break;

                }

                else{

                    validacion=true;
                    //cout<<endl<<"Es operacion XOR"<<endl;

                }

            }


        }

        if (validacion==true){

            cout<<endl<<"Es operacion desplazamiento a la izquierda de "<<j<<"bits"<<endl;

            break;

        }

        else{

            cout<<endl<<"No es operacion desplazamiento a la izquierda de "<<j<<"bits"<<endl;

            for (int i = 0; i < totalSize; i++) {

                // Original rotar a la derecha
                validacData[i] = desplazamientoIzq(validacData[i], j);
                //validacData[i] = rotacionDer(validacData[i], j);
            }



        }


        cout<<endl<<"Bandera con j"<<j<<" "<<validacion<<endl;

    }

    if (validacion==true){
        break;
    }

    delete [] validacionData;

    }


    while(validacion==false);



    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }

    if (maskingData1 != nullptr){
        delete[] maskingData1;
        maskingData1 = nullptr;
    }

    delete [] pixelData;
    pixelData = nullptr;

    delete [] maskData;
    delete [] original;
    delete [] validacData;

    delete [] ImaskData;
    ImaskData = nullptr;



    return 0; // Fin del programa
}


/* ******************************** Funiciones ************************************** */

unsigned char* loadPixels(QString input, int &width, int &height){
    /*
 * @brief Carga una imagen BMP desde un archivo y extrae los datos de píxeles en formato RGB.
 *
 * Esta función utiliza la clase QImage de Qt para abrir una imagen en formato BMP, convertirla al
 * formato RGB888 (24 bits: 8 bits por canal), y copiar sus datos de píxeles a un arreglo dinámico
 * de tipo unsigned char. El arreglo contendrá los valores de los canales Rojo, Verde y Azul (R, G, B)
 * de cada píxel de la imagen, sin rellenos (padding).
 *
 * @param input Ruta del archivo de imagen BMP a cargar (tipo QString).
 * @param width Parámetro de salida que contendrá el ancho de la imagen cargada (en píxeles).
 * @param height Parámetro de salida que contendrá la altura de la imagen cargada (en píxeles).
 * @return Puntero a un arreglo dinámico que contiene los datos de los píxeles en formato RGB.
 *         Devuelve nullptr si la imagen no pudo cargarse.
 *
 * @note Es responsabilidad del usuario liberar la memoria asignada al arreglo devuelto usando `delete[]`.
 */

    // Cargar la imagen BMP desde el archivo especificado (usando Qt)
    QImage imagen(input);

    // Verifica si la imagen fue cargada correctamente
    if (imagen.isNull()) {
        cout << "Error: No se pudo cargar la imagen BMP." << std::endl;
        return nullptr; // Retorna un puntero nulo si la carga falló
    }

    // Convierte la imagen al formato RGB888 (3 canales de 8 bits sin transparencia)
    imagen = imagen.convertToFormat(QImage::Format_RGB888);

    // Obtiene el ancho y el alto de la imagen cargada
    width = imagen.width();
    height = imagen.height();

    //cout<<endl<<"Ancho: "<<width<<" "<<"Alto: "<<height<<endl;

    // Calcula el tamaño total de datos (3 bytes por píxel: R, G, B)
    int dataSize = width * height * 3;

    // Reserva memoria dinámica para almacenar los valores RGB de cada píxel
    unsigned char* pixelData = new unsigned char[dataSize];

    //cout<<endl<<"pixel Data: "<<*(pixelData+3)<<endl;

    // Copia cada línea de píxeles de la imagen Qt a nuestro arreglo lineal
    for (int y = 0; y < height; ++y) {
        const uchar* srcLine = imagen.scanLine(y);              // Línea original de la imagen con posible padding
        unsigned char* dstLine = pixelData + y * width * 3;     // Línea destino en el arreglo lineal sin padding
        memcpy(dstLine, srcLine, width * 3);                    // Copia los píxeles RGB de esa línea (sin padding)

        //cout<<endl<<"dstLine: "<<*(dstLine)<<endl;
    }

    // Retorna el puntero al arreglo de datos de píxeles cargado en memoria
    //cout<<endl<<"pixel Data: "<<(pixelData)<<endl;

    return pixelData;

}

bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida){
    /*
 * @brief Exporta una imagen en formato BMP a partir de un arreglo de píxeles en formato RGB.
 *
 * Esta función crea una imagen de tipo QImage utilizando los datos contenidos en el arreglo dinámico
 * `pixelData`, que debe representar una imagen en formato RGB888 (3 bytes por píxel, sin padding).
 * A continuación, copia los datos línea por línea a la imagen de salida y guarda el archivo resultante
 * en formato BMP en la ruta especificada.
 *
 * @param pixelData Puntero a un arreglo de bytes que contiene los datos RGB de la imagen a exportar.
 *                  El tamaño debe ser igual a width * height * 3 bytes.
 * @param width Ancho de la imagen en píxeles.
 * @param height Alto de la imagen en píxeles.
 * @param archivoSalida Ruta y nombre del archivo de salida en el que se guardará la imagen BMP (QString).
 *
 * @return true si la imagen se guardó exitosamente; false si ocurrió un error durante el proceso.
 *
 * @note La función no libera la memoria del arreglo pixelData; esta responsabilidad recae en el usuario.
 */

    // Crear una nueva imagen de salida con el mismo tamaño que la original
    // usando el formato RGB888 (3 bytes por píxel, sin canal alfa)
    QImage outputImage(width, height, QImage::Format_RGB888);

    // Copiar los datos de píxeles desde el buffer al objeto QImage
    for (int y = 0; y < height; ++y) {
        // outputImage.scanLine(y) devuelve un puntero a la línea y-ésima de píxeles en la imagen
        // pixelData + y * width * 3 apunta al inicio de la línea y-ésima en el buffer (sin padding)
        // width * 3 son los bytes a copiar (3 por píxel)
        memcpy(outputImage.scanLine(y), pixelData + y * width * 3, width * 3);
    }

    // Guardar la imagen en disco como archivo BMP
    if (!outputImage.save(archivoSalida, "BMP")) {
        // Si hubo un error al guardar, mostrar mensaje de error
        cout << "Error: No se pudo guardar la imagen BMP modificada.";
        return false; // Indica que la operación falló
    } else {
        // Si la imagen fue guardada correctamente, mostrar mensaje de éxito
        cout << "Imagen BMP modificada guardada como " << archivoSalida.toStdString() << endl;
        return true; // Indica éxito
    }

}

unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels){
    /*
 * @brief Carga la semilla y los resultados del enmascaramiento desde un archivo de texto.
 *
 * Esta función abre un archivo de texto que contiene una semilla en la primera línea y,
 * a continuación, una lista de valores RGB resultantes del proceso de enmascaramiento.
 * Primero cuenta cuántos tripletes de píxeles hay, luego reserva memoria dinámica
 * y finalmente carga los valores en un arreglo de enteros.
 *
 * @param nombreArchivo Ruta del archivo de texto que contiene la semilla y los valores RGB.
 * @param seed Variable de referencia donde se almacenará el valor entero de la semilla.
 * @param n_pixels Variable de referencia donde se almacenará la cantidad de píxeles leídos
 *                 (equivalente al número de líneas después de la semilla).
 *
 * @return Puntero a un arreglo dinámico de enteros que contiene los valores RGB
 *         en orden secuencial (R, G, B, R, G, B, ...). Devuelve nullptr si ocurre un error al abrir el archivo.
 *
 * @note Es responsabilidad del usuario liberar la memoria reservada con delete[].
 */

    // Abrir el archivo que contiene la semilla y los valores RGB
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        // Verificar si el archivo pudo abrirse correctamente
        cout << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }

    // Leer la semilla desde la primera línea del archivo
    archivo >> seed;

    int r, g, b;

    // Contar cuántos grupos de valores RGB hay en el archivo
    // Se asume que cada línea después de la semilla tiene tres valores (r, g, b)
    while (archivo >> r >> g >> b) {
        n_pixels++;  // Contamos la cantidad de píxeles
    }

    // Cerrar el archivo para volver a abrirlo desde el inicio
    archivo.close();
    archivo.open(nombreArchivo);

    // Verificar que se pudo reabrir el archivo correctamente
    if (!archivo.is_open()) {
        cout << "Error al reabrir el archivo." << endl;
        return nullptr;
    }

    // Reservar memoria dinámica para guardar todos los valores RGB
    // Cada píxel tiene 3 componentes: R, G y B
    unsigned int* RGB = new unsigned int[n_pixels * 3];

    // Leer nuevamente la semilla desde el archivo (se descarta su valor porque ya se cargó antes)
    archivo >> seed;

    // Leer y almacenar los valores RGB uno por uno en el arreglo dinámico
    for (int i = 0; i < n_pixels * 3; i += 3) {
        archivo >> r >> g >> b;
        RGB[i] = r;
        RGB[i + 1] = g;
        RGB[i + 2] = b;
    }

    // Cerrar el archivo después de terminar la lectura
    archivo.close();

    // Mostrar información de control en consola
    cout << "Semilla: " << seed << endl;
    cout << "Cantidad de pixeles leidos: " << n_pixels << endl;

    // Retornar el puntero al arreglo con los datos RGB
    return RGB;
}

unsigned char desplazamientoIzq(unsigned char Id, int n){

    return Id << n;

}

unsigned char desplazamientoDer(unsigned char Id, int n){

    return Id >> n;

}

unsigned char rotacionIzq(unsigned char Id, int n){

    return (Id << n) | (Id >> (8 - n));

}

unsigned char rotacionDer(unsigned char Id, int n){

    return (Id >> n) | (Id << (8 - n));

}

unsigned char operacionXor(unsigned char Id, unsigned char IM){

    return Id ^ IM;

}

unsigned char* revertirEnmas(unsigned int* sumaRGB, unsigned char* M, int i, int j){

    unsigned char* original = new unsigned char[i*j*3];


    for (int k=0;k<(i*j*3);k++){

        int valor=(int)sumaRGB[k]-(int)M[k];

        if (valor < 0){
            valor += 256;  // Evitar desbordamiento negativo
        }

        original[k] = (unsigned char)(valor);

    }

    return original;

}

void enmascaramiento(unsigned char* Id, int wId, int hId, unsigned char* M, int wM, int hM, int s){

    int totalId=wId*hId*3;
    int totalM=wM*hM*3;

    // Validar tamaños
    if (totalId < totalM) {
        cout << "Error: La imagen ID es más pequeña que la máscara M." << endl;
        return;
    }

    // Abrir archivo para guardar salida
    ofstream archivo("Validacion.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    // Escribir la semilla en la primera línea
    archivo << s << endl;

    // Calcular y guardar las sumas S(k) = ID(k + s) + M(k)
    for (int k = 0; k < totalM; k += 3) {
        int r = (int)Id[s + k]     +(int)M[k];
        int g = (int)Id[s + k + 1] + (int)M[k + 1];
        int b = (int)Id[s + k + 2] + (int)M[k + 2];

        archivo << r << " " << g << " " << b << endl;
    }

    archivo.close();
    cout << "Enmascaramiento completado. Archivo guardado: " << "Validacion.txt"<< endl;

}







