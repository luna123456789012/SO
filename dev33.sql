DROP DATABASE IF EXISTS juego;
CREATE DATABASE juego;
USE juego;

CREATE TABLE jugadores (
	ID_j INT PRIMARY KEY NOT NULL,
	usuario TEXT NOT NULL,
	contraseña TEXT,
)ENGINE = InnoDB;

CREATE TABLE jugadores_partida (
    ID_j INT NOT NULL,
    ID_p INT NOT NULL,
    PRIMARY KEY (ID_j, ID_p),
    FOREIGN KEY (ID_j) REFERENCES jugadores(ID_j) ON DELETE CASCADE,
    FOREIGN KEY (ID_p) REFERENCES partida(ID_p) ON DELETE CASCADE
) ENGINE = InnoDB;

CREATE TABLE partida(
ID_p INTEGER PRIMARY KEY AUTO_INCREMENT,
                        tipo TEXT NOT NULL,
                        num_jugadores INTEGER NOT NULL,
                        ID_ganador INTEGER
)ENGINE = InnoDB;


INSERT INTO jugadores (ID_j, usuario, contraseña) VALUES (1, 'alvaro', 'piano42');
INSERT INTO jugadores (ID_j, usuario, contraseña) VALUES (2, 'marta', '5pistacho');
INSERT INTO jugadores (ID_j, usuario, contraseña) VALUES (3, 'paula', '86flor');
INSERT INTO jugadores (ID_j, usuario, contraseña) VALUES (4, 'didac', 'casa00');
INSERT INTO jugadores (ID_j, usuario, contraseña) VALUES (5, 'daniel', 'so2025');

INSERT INTO partida (ID_p, tipo, num_jugadores, ID_ganador) VALUES (1, 2, 2, 1);
INSERT INTO partida (ID_p, tipo, num_jugadores, ID_ganador) VALUES (2, 2, 2, 1);
INSERT INTO partida (ID_p, tipo, num_jugadores, ID_ganador) VALUES (3, 2, 2, 2);
INSERT INTO partida (ID_p, tipo, num_jugadores, ID_ganador) VALUES (4, 2, 2, 2);

INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (1,1);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (1,4);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (2,3);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (2,1);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (3,4);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (3,2);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (4,2);
INSERT INTO jugadores_partida (ID_j, ID_p) VALUES (4,1);
