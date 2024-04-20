En este *repl* puedes encontrar varios ejemplos que te pueden ayudar con las tareas de estructura.

## Como correr el codigo
````
Se configuro el programa para ser ejecutado con el boton Run
````

## Código de Ejemplo (main)
Para ejecutar el main primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````
./main
````

## TDAs
En la carpeta `tdas` se encuentran implementados distintos TDAs que puedes utilizar (lista, pila, cola, cola con prioridad y mapas). 

Las implementaciones no son las más eficientes (todas usan como estructura de datos una **lista enlazada**), por lo que puedes reemplazarlas por las que has realizado en los labs.

## Otros códigos (en carpeta examples)
Para ejecutar los distintos ejemplos que hay en la carpeta `examples`, primero debes compilarlos. Si estamos en la carpeta raíz:
````
gcc tdas/*.c examples/example2_menu.c -Wno-unused-result -o example
````
Y luego ejecutarlos:
````
./example
````

Se incluyen los siguientes ejemplos:
* `example1_list`: Uso del TDA Lista, inserción y eliminación de elementos.
* `example2_menu`: Ejemplo de menú con submenús.
* `example3_readcsv`: Ejemplo de lectura desde un archivo csv y almacenamiento en datos estructurados.
* `example4_map`: Ejemplo de uso del TDA mapa.