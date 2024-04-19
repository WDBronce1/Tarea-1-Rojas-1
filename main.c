#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "tdas/list.h"


typedef struct Persona{
  char nombre[60];
  int edad;
  char sintomas[150];
}Persona;

typedef struct Paciente{
  Persona persona;
  int Prioridad;
  int HoraLlegada;
}Paciente;

typedef struct Filas{
  List *FilaAlta;
  List *FilaMedia;
  List *FilaBaja;
}Filas;

Filas* create_Filas(void)
{
  Filas* newFila = malloc(sizeof(Filas));
  newFila->FilaAlta = list_create();
  newFila->FilaMedia = list_create();
  newFila->FilaBaja = list_create();
  return newFila;
}

// Funciones ****************************************************************

//Registrar paciente  ########################################################
//El usuario ingresa los datos del paciente. La aplicación registra al paciente con la hora de registro actual y asigna automáticamente un nivel de prioridad "Bajo" inicialmente.
void registrar_paciente(List *lista_pacientes, Filas *fila)
{
  Paciente *paciente = malloc(sizeof(Paciente));
  getchar();
  printf("Ingrese el nombre del paciente: ");
  fgets(paciente->persona.nombre, sizeof(paciente->persona.nombre), stdin);
  printf("\n");
  printf("Ingrese la edad del paciente: ");
  scanf("%d", &paciente->persona.edad);
  printf("\n");
  getchar();
  printf("Ingrese los sintomas del paciente: ");
  fgets(paciente->persona.sintomas, sizeof(paciente->persona.sintomas), stdin);
  printf("\n");
  printf("Ingrese la hora de llegada del paciente: ");
  scanf("%d", &paciente->HoraLlegada);
  printf("\n");
  strcpy(paciente->Prioridad,"Baja");
  list_pushBack(lista_pacientes, paciente);
  list_pushBack(fila->FilaBaja, paciente);
}


//Asignar Prioridad ##########################################################
//El usuario ingresa el nombre del paciente y el nuevo nivel de prioridad ("Alto", "Medio", "Bajo"). La aplicación actualiza el nivel de prioridad del paciente. Si el paciente no existe, se muestra un aviso.

void asignar_prioridad(List *lista_pacientes, Filas *fila)
{
  char PacienteBuscado[60];
  char NuevaPrioridad[30];
  Paciente* PacienteActual = malloc(sizeof(Paciente));
  PacienteActual = list_first(lista_pacientes);
  printf("Ingrese el nombre del paciente a buscar: ");
  getchar();
  fgets(PacienteBuscado, sizeof(PacienteBuscado), stdin);
  while(strcmp(PacienteActual->persona.nombre,PacienteBuscado) != 0 && PacienteActual != NULL)
    {
      PacienteActual = list_next(lista_pacientes);
    }
  if(PacienteActual == NULL)
  {
    printf("El paciente no existe\n");
  }
  else
  {
    list_popCurrent(fila->FilaMedia);
    list_popCurrent(fila->FilaAlta);
    
    printf("Ingrese la prioridad a asignar (Alta | Media | Baja)\n");
    getchar();
    fgets(NuevaPrioridad, sizeof(NuevaPrioridad), stdin);
    
    strcpy(PacienteActual->Prioridad, NuevaPrioridad);
  }
  
  
}


//Mostrar lista de espera ####################################################
// La aplicación muestra por pantalla la lista de pacientes en espera, ordenada por nivel de prioridad (de "Alto" a "Bajo") y, dentro del mismo nivel, por orden de llegada (hora de registro).
void mostrar_lista_pacientes(List *lista_pacientes, Filas *fila, int pacientes) 
{
  Paciente* PacienteActual = malloc(sizeof(Paciente));
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: %d\n", pacientes);
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  
  PacienteActual = list_first(fila->FilaAlta);
  while (PacienteActual != NULL)
    {
      printf("Nombre: %s\n", PacienteActual->persona.nombre);
      printf("                         Hora de llegada : %d", PacienteActual->HoraLlegada);
      printf("\n");
      PacienteActual = list_next(fila->FilaAlta);
    }
  
  PacienteActual = list_first(fila->FilaMedia);
  while (PacienteActual != NULL)
  {
    printf("Nombre: %s\n", PacienteActual->persona.nombre);
    printf("                         Hora de llegada : %d", PacienteActual->HoraLlegada);
    printf("\n");
    PacienteActual = list_next(fila->FilaMedia);
  }
  
  PacienteActual = list_first(fila->FilaBaja);
  while (PacienteActual != NULL)
  {
    printf("Nombre: %s\n", PacienteActual->persona.nombre);
    printf("                         Hora de llegada : %d", PacienteActual->HoraLlegada);
    printf("\n");
    PacienteActual = list_next(fila->FilaBaja);
  }
  
}
//Atender al siguiente paciente ##############################################
//La aplicación selecciona al siguiente paciente a ser atendido según el orden de prioridad y lo elimina de la lista de espera. Muestra los datos del paciente atendido. Si no hay pacientes en espera, se muestra un aviso.
/*
void atender_paciente(List *lista_pacientes, Filas *fila)
{
  Paciente *PacienteActual = malloc(sizeof(Paciente));
  Paciente *Auxiliar = malloc(sizeof(Paciente));
  if (list_first(fila->FilaAlta) != NULL)
  {
    PacienteActual = list_first(fila->FilaAlta);
    Auxiliar = PacienteActual;
    list_popFront(fila->FilaAlta);
  }
  else 
    if (list_first(fila->FilaMedia) != NULL)
    {
      PacienteActual = list_first(fila->FilaMedia);
      Auxiliar = PacienteActual;
      list_popFront(fila->FilaMedia);
    }
  else 
    if (list_first(fila->FilaBaja) != NULL)
    {
      PacienteActual = list_first(fila->FilaBaja);
      Auxiliar = PacienteActual;
      list_popFront(fila->FilaBaja);
    }
   else
  {
    printf("NO HAY LISTA DE ESPERA\n");
    return;
  }
  printf("Datos del Paciente atendido:\n");
  printf("Nombre: %s\n", Auxiliar->persona.nombre);
  printf("Edad: %d\n", Auxiliar->persona.edad);
  printf("Sintomas: %s\n", Auxiliar->persona.sintomas);
  printf("Hora de llegada: %d\n", Auxiliar->HoraLlegada);
  printf("Prioridad: %s\n", Auxiliar->Prioridad);
  list_popCurrent(lista_pacientes);
}
*/
void atender_paciente(List *lista_pacientes, Filas *fila)
{
  Paciente *PacienteActual = NULL;
  Paciente *Auxiliar = malloc(sizeof(Paciente));
  if (list_first(fila->FilaAlta) != NULL)
  {
    PacienteActual = list_first(fila->FilaAlta);
    Auxiliar = PacienteActual;
    list_popFront(fila->FilaAlta);
  }
  else if (list_first(fila->FilaMedia) != NULL)
  {
    PacienteActual = list_first(fila->FilaMedia);
    Auxiliar = PacienteActual;
    list_popFront(fila->FilaMedia);
  }
  else if (list_first(fila->FilaBaja) != NULL)
  {
    PacienteActual = list_first(fila->FilaBaja);
    Auxiliar = PacienteActual;
    list_popFront(fila->FilaBaja);
  }
  else
  {
    printf("NO HAY PACIENTES EN ESPERA\n");
    return;
  }
  printf("Datos del Paciente atendido:\n");
  printf("Nombre: %s\n", Auxiliar->persona.nombre);
  printf("Edad: %d\n", Auxiliar->persona.edad);
  printf("Sintomas: %s\n", Auxiliar->persona.sintomas);
  printf("Hora de llegada: %d\n", Auxiliar->HoraLlegada);
  printf("Prioridad: %s\n", Auxiliar->Prioridad);

  list_popCurrent(lista_pacientes);
}
//Mostrar pacientes por prioridad ############################################
//El usuario ingresa un nivel de prioridad y la aplicación muestra por pantalla los pacientes que corresponden a ese nivel, ordenados por orden de llegada.
void mostrar_pacientes_por_prioridad(List *lista_pacientes, Filas *fila)
{
  Paciente *PacienteActual = malloc(sizeof(Paciente));
  char PrioridadBuscada[30];
  printf("Ingrese la prioridad: ");
  scanf("%s", PrioridadBuscada);

  if(strcasecmp(PrioridadBuscada, "Alta") == 0)
  {
    PacienteActual = list_first(fila->FilaAlta);
    while(PacienteActual != NULL)
    {
      printf("Nombre: %s\n", PacienteActual->persona.nombre);
      printf("                         Hora de llegada : %d", PacienteActual->HoraLlegada);
      printf("\n");
      PacienteActual = list_next(fila->FilaAlta);
    }
  }
  else if(strcasecmp(PrioridadBuscada, "Media") == 0)
  {
    PacienteActual = list_first(fila->FilaMedia);
    while(PacienteActual != NULL)
    {
      printf("Nombre: %s\n", PacienteActual->persona.nombre);
      printf("                         Hora de llegada : %d", PacienteActual->HoraLlegada);
      printf("\n");
      PacienteActual = list_next(fila->FilaMedia);
    }
  }
  else if(strcasecmp(PrioridadBuscada, "Baja") == 0)
  {
    PacienteActual = list_first(fila->FilaBaja);
    while(PacienteActual != NULL)
    {
      printf("Nombre: %s\n", PacienteActual->persona.nombre);
      printf("                         Hora de llegada : %d", PacienteActual->HoraLlegada);
      printf("\n");
      PacienteActual = list_next(fila->FilaBaja);
    }
  }
}
//****************************************************************************

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}



int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes
  Filas *filas = create_Filas();
  int CantidadPacientes = 0;

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) 
    {
      case '1':
        registrar_paciente(pacientes, filas);
        CantidadPacientes++;
        break;
      case '2':
        // Lógica para asignar prioridad
        asignar_prioridad(pacientes, filas);
        break;
      case '3':
        mostrar_lista_pacientes(pacientes, filas, CantidadPacientes);
        break;
      case '4':
        // Lógica para atender al siguiente paciente
        atender_paciente(pacientes, filas);
        CantidadPacientes--;
        break;
      case '5':
        // Lógica para mostrar pacientes por prioridad
        mostrar_pacientes_por_prioridad(pacientes, filas);
        break;
      case '6':
        puts("Saliendo del sistema de gestión hospitalaria...");
        break;
      default:
        puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);
  

  return 0;
}
