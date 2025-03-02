#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "DatosConexion.h"

int conectar(MYSQL **conn);
void ejecutar_consulta(MYSQL *conn, char *consulta);

int main(int argc, char *argv[]) {
    int error;
    char *consulta;
    MYSQL *conn;

    error = conectar(&conn);
    if (!error) {
        // Consulta que agrupa por jugador, contando las partidas jugadas y sumando las ganadas.
        consulta = "SELECT jugadores.usuario FROM jugadores, jugadores_partida, partida "
                   "WHERE jugadores.ID_j = jugadores_partida.ID_j AND jugadores_partida.ID_p = partida.ID_p "
                   "AND partida.ID_ganador = jugadores.ID_j"
                   "AND (SELECT SUM(partida.ID_ganador = jugadores.ID_j) FROM partida, jugadores_partida"
                   "WHERE partida.ID_p = jugadores_partida.ID_p"
                   "AND jugadores_partida.ID_j = jugadores.ID_j) >= 2;";
        ejecutar_consulta(conn, consulta); 
        mysql_close(conn); 
    }
    return 0;
}

int conectar(MYSQL **conn){ 
    int error; 
    *conn = mysql_init(NULL);
    
    if (mysql_real_connect(*conn, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) != NULL){
        printf("Se estableció la conexión con la base de datos\n");
        error = 0;
    }
    else{
        printf("Error al conectarse con la base de datos: %s\n", mysql_error(*conn));
        error = 1; 
    }
    return error;
}

void ejecutar_consulta(MYSQL *conn, char *consulta) {
    int error;
    MYSQL_RES *res_ptr; 
    MYSQL_ROW res_fila;

    error = mysql_query(conn, consulta);
    if (!error) {
        res_ptr = mysql_store_result(conn); 
        if (res_ptr) {
            int hay_ganadores = 0; 

            while ((res_fila = mysql_fetch_row(res_ptr)) != NULL) {
                if (!hay_ganadores) {
                    printf("Los jugadores que han ganado dos o más partidas son:\n");
                    hay_ganadores = 1;
                }
                printf("- %s ha ganado %s partidas.\n",
                    res_fila[0] ? res_fila[0] : "NULL",  
                    res_fila[1] ? res_fila[1] : "0");   
            }

            if (!hay_ganadores) {
                printf("No hay jugadores que hayan ganado dos o más partidas.\n");
            }

            mysql_free_result(res_ptr);
        } else {
            printf("Error al obtener el resultado: %u %s\n", mysql_errno(conn), mysql_error(conn));
        }
    } else {
        printf("Error al ejecutar la consulta: %u %s\n", mysql_errno(conn), mysql_error(conn));
    }
}
