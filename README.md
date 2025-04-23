Desafío 1

Especificaciones

La empresa Informa2 necesita desarrollar un programa capaz de reconstruir una imagen original a partir de la siguiente información:

• Una imagen ID de dimensiones m filas por n columnas, con tres canales (RGB), que representa el resultado final tras haber sido sometida a una serie de transformaciones a nivel de bits, 
  aplicadas en un orden desconocido.
  
• Una imagen IM, también de m filas por n columnas y tres canales (RGB), generada aleatoriamente, que pudo haber sido utilizada en una o varias ocasiones durante el proceso de transformación 
  mediante operaciones XOR con versiones intermedias de ID.
  
• Una máscara M, de dimensiones i ≤ m filas y j ≤ n columnas, con tres canales (RGB), utilizada para aplicar un enmascaramiento después de cada transformación a nivel de bits. 
  Este enmascaramiento consiste en seleccionar aleatoriamente un píxel de desplazamiento s en la imagen transformada ID, y a partir de este calcular las sumas:
  
                                                               S(k) = ID(k + s) + M(k) para 0 ≤ k < i × j × 3
                                                               
• N archivos .txt, que contienen la información generada durante el enmascaramiento aplicado en cada etapa del proceso.  Cada archivo incluye:

    o En la primera línea, un valor entero que representa el desplazamiento s utilizado para aplicar el enmascaramiento.
    o En las líneas siguientes, conjuntos de tres valores enteros que representan la suma de los canales RGB, píxel a píxel, entre una porción transformada de ID y la máscara M.
 
 De acuerdo con lo anterior, entre otras cosas, usted deberá:
    [15%] Escribir funciones para realizar operaciones a nivel de bit, tales como XOR, desplazamiento y rotación de bits. El máximo número de bits a rotar o desplazar es de 8.
    [10%] Realizar experimentos con las diferentes operaciones a nivel de bit y analizar el efecto de las transformaciones sobre la integridad de los datos y su utilidad en un escenario de encriptación básica de información.
    [10%] Implementar un algoritmo que permita verificar el resultado del enmascaramiento, comparando la imagen transformada y la máscara contra los archivos de resultados.
    [65%] Implementar un algoritmo que permita identificar qué tipo de operaciones a nivel de bits fueron realizadas (y en qué orden), con el fin de reconstruir la imagen original.
 
