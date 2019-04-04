#ifndef MENUES_H_INCLUDED
#define MENUES_H_INCLUDED

#include "peliculas.h"
#include "usuarios.h"
#include "clientes.h"
#include "reportes.h"


enum Color{
cNEGRO=0,
cAZUL=1,
cVERDE=2,
cCIAN=3,
cROJO=4,
cMAGENTA=5,
cMARRON=6,
cGRIS_CLARO=7,
cGRIS=8,
cAZUL_CLARO=9,
cVERDE_CLARO=10,
cCIAN_CLARO=11,
cROJO_CLARO=12,
cMAGENTA_CLARO=13,
cAMARILLO=14,
cBLANCO=15
};



void textcolor(short colorTexto=15, short colorFondo=0){
    short color = colorTexto + colorFondo * 16;
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color);
}

void recuadro(short iniX, short iniY, short ancho, short alto, short colorLinea=cVERDE, short colorFondo=cNEGRO){
    int i, j;
    for(i=iniX; i<=iniX+ancho; i++){
        for(j=iniY; j<=iniY+alto; j++){
            gotoXY(i,j);
            textcolor(colorLinea, colorFondo);
            ///Arriba izquierda
            if(i==iniX && j==iniY){
                cout << (char) 201;
            }
            ///Arriba derecha
            else if(i==iniX+ancho && j==iniY){
                cout << (char) 187;
            }
            ///Abajo izquierda
            else if(i==iniX && j==iniY+alto){
                cout << (char) 200;
            }
            ///Abajo derecha
            else if(i==iniX+ancho && j==iniY+alto){
                cout << (char) 188;
            }
            ///Lineas arriba y abajo
            else if(j==iniY || j==iniY+alto){
                cout << (char) 205;
            }
            ///Lineas izquierda y derecha
            else if(i==iniX || i==iniX+ancho){
                cout << (char) 186;
            }
            ///Dentro del recuadro
            else{
                cout << " ";
            }
        }
    }
}

COORD Mouse(){
        HANDLE hout= GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
        INPUT_RECORD InputRecord;
        DWORD Events;
        COORD coord;
        CONSOLE_CURSOR_INFO cci;
        cci.dwSize = 25;
        cci.bVisible = TRUE;
        SetConsoleCursorInfo(hout, &cci);

        SetConsoleMode(hin,  ENABLE_EXTENDED_FLAGS  | ENABLE_INSERT_MODE  | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);


    while(1)
    {

        ReadConsoleInput(hin, &InputRecord, 1, &Events);

        if(InputRecord.EventType == MOUSE_EVENT)
        {
            if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
                coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
                SetConsoleCursorPosition(hout,coord);
                SetConsoleTextAttribute(hout,14);

                return coord;
                /**if(coord.X>=cordenadaX1&&coord.X<=cordenadaX2){
                 //  cout<<"entro"<<endl;pause();
                    if(coord.Y>=cordenadaY1 && coord.Y<=cordenadaY2){return coord.Y;
                    //return true;
                    }

                }**/
               /// break;
            }
        }
        FlushConsoleInputBuffer(hin);

    }
coord.X=0;
coord.Y=0;
return coord;
///return -1;
//return false;
}

bool clikeo (COORD click, int yi , int yf){
if (click.X>=25 && click.X<=45){
    if(click.Y>=yi && click.Y<=yf){
        return true;
    }
}
return false;
}

void submenu_usuarios_reportes(char *us){
COORD click;
fflush(stdin);
system("cls");

while (true){
system("cls");
gotoXY(50,0); cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(25,7);cout << "LISTAR ADMINS";
recuadro(22,10,30,3);
gotoXY(30,12);cout << "LISTAR CLIENTES";
gotoXY(25,15);cout <<"*********************";
recuadro(22,17,30,3);
gotoXY(32,19);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    listar_admins();
    fflush(stdin);
    break;
}else if (clikeo(click,10,13)){
    listar_clientes();
    fflush(stdin);
    break;
}else if (clikeo(click,17,20)){
    cout << "VOLVER";
    fflush(stdin);
    return;
    }
}


}


}



void menu_usuarios (char *us){
fflush(stdin);
system("cls");
COORD click;
admin ad;
cliente cl;
click.X=0;
click.Y=0;


while (true){
system("cls");
gotoXY(50,0);cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(27,7);cout << "NUEVO ADMINISTRADOR";
recuadro(22,10,30,3);
gotoXY(30,12);cout << "NUEVO CLIENTE";
recuadro(22,15,30,3);
gotoXY(25,17);cout << "DAR DE BAJA ADMINISTRADOR";
recuadro(22,20,30,3);
gotoXY(30,22);cout << "DAR DE BAJA CLIENTE";
recuadro(22,25,30,3);
gotoXY(30,27);cout << "DAR DE ALTA CLIENTE";
recuadro(22,30,30,3);
gotoXY(31,32);cout << "LISTADOS";
gotoXY(22,35);cout <<"*******************************";
recuadro(22,36,30,3);
gotoXY(33,38);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    cout <<"nuevo admin";
   nuevoadmin();
    fflush(stdin);
   system("cls");
    break;
} else if (clikeo(click,10,13)){
    cout << "neuvo cliente" <<endl;
    nuevocliente(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,15,18)){
    cout << "baja admin";
    baja_usuario(ad,"admins.dat");
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,20,23)){
    cout << "baja cliente" <<endl;
    baja_usuario(cl,"clientes.dat");
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,25,28)){
    cout << "alta cliente" <<endl;
    fflush(stdin);
    dar_de_alta();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,30,33)){
    cout << "Reportes" <<endl;
    fflush(stdin);
    submenu_usuarios_reportes(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,36,39)){
    cout << "volver" <<endl;
    system("cls");
    fflush(stdin);
    return;
}


}

}
}

void menupeliculas (char *us) {
fflush(stdin);
system("cls");
fflush(stdin);
COORD click;

while (true){
    gotoXY(50,0);cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(25,5,25,3);
gotoXY(30,7);cout << "NUEVO PELICULA";
recuadro(25,10,25,3);
gotoXY(30,12);cout << "LISTAR PELICULA";
recuadro(25,15,25,3);
gotoXY(27,17);cout << "LISTAR TODOS PELICULAS";
recuadro(25,20,25,3);
gotoXY(30,22);cout << "EDITAR PELICULA";
recuadro(25,25,25,3);
gotoXY(30,27);cout << "ELIMINAR PELICULA";
gotoXY(25,32);cout <<"************************";
recuadro(25,34,25,3);
gotoXY(26,36);cout << "VOLVER A MENU PRINCIPAL ";
cout<<endl<<endl<<endl;



while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    fflush(stdin);
    newpelicula(us);
    fflush(stdin);
    break;
} else if (clikeo(click,10,13)){
    fflush(stdin);
    listar_pelicula();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,15,18)){
    listarpeliculas();
    fflush(stdin);
    break;
} else if (clikeo(click,20,23)){
   editar_pel();
   fflush(stdin);
   system("cls");
    break;
} else if (clikeo(click,25,28)){
    baja_pelicula();
    fflush(stdin);
  system("cls");
    break;
} else if (clikeo(click,34,39)){
    cout << "VOLVER" <<endl;
    fflush(stdin);
    return;
}


}

}
system("cls");

}

void menudirectores (char *us){     ///LISTO
fflush(stdin);
system("cls");
COORD click;

while (true){
    gotoXY(50,0);cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(25,5,25,3);
gotoXY(30,7);cout << "NUEVO DIRECTOR";
recuadro(25,10,25,3);
gotoXY(30,12);cout << "LISTAR DIRECTOR";
recuadro(25,15,25,3);
gotoXY(27,17);cout << "LISTAR TODOS DIRECTORES";
recuadro(25,20,25,3);
gotoXY(30,22);cout << "EDITAR DIRECTOR";
recuadro(25,25,25,3);
gotoXY(30,27);cout << "ELIMINAR DIRECTOR";
gotoXY(25,30);cout <<"*************************";
recuadro(25,32,25,3);
gotoXY(26,34);cout << "VOLVER A MENU PRINCIPAL ";
cout<<endl<<endl<<endl;



while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    fflush(stdin);
    nuevodirector();
    system("cls");
    break;
} else if (clikeo(click,10,13)){
    fflush(stdin);
    listar_dir_id();
    system("cls");
    break;
} else if (clikeo(click,15,18)){
    fflush(stdin);
    listardirectores();
    break;
} else if (clikeo(click,20,23)){
    fflush(stdin);
    editar_dir();
    system("cls");
    break;
} else if (clikeo(click,25,28)){
    fflush(stdin);
    baja_director();
    system("cls");
    break;
} else if (clikeo(click,32,35)){
    cout << "VOLVER" <<endl;
    fflush(stdin);
    return;
}


}

}
system("cls");
}

void submenu_bkp_rest (char *us){
fflush(stdin);
system("cls");
COORD click;
string ruta,destino;

while (true){
system("cls");
gotoXY(50,0); cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(25,7);cout << "RESTAURAR BACKUP DIRECTORES";
recuadro(22,10,30,3);
gotoXY(25,12);cout << "RESTAURAR BACKUP PELICULAS";
recuadro(22,15,30,3);
gotoXY(25,17);cout << "RESTAURAR BACKUP ADMINS";
recuadro(22,20,30,3);
gotoXY(25,22);cout << "RESTAURAR BACKUP VENTAS";
recuadro(22,25,30,3);
gotoXY(25,27);cout << "RESTAURAR BACKUP CLIENTES";
recuadro(22,30,30,3);
gotoXY(25,32);cout << "RESTAURAR BACKUP ALQUILERES";
recuadro(22,35,30,3);
gotoXY(25,37);cout << "RESTAURAR TODO";
gotoXY(25,40);cout <<"*********************";
recuadro(22,41,30,3);
gotoXY(32,43);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    ruta="directores.bkp";
    destino="directores.dat";
    copy_file(ruta,destino);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,10,13)){
    ruta="peliculas.bkp";
    destino="peliculas.dat";
    copy_file(ruta,destino);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,15,18)){
    ruta="admins.bkp";
    destino="admins.dat";
    copy_file(ruta,destino);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,20,23)){
    ruta="ventas.bkp";
    destino="ventas.dat";
    copy_file(ruta,destino);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,25,28)){
    ruta="clientes.bkp";
    destino="clientes.dat";
    copy_file(ruta,destino);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,30,33)){
    ruta="alquileres.bkp";
    destino="alquileres.dat";
    copy_file(ruta,destino);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,35,38)){
   rest_todo();
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,41,44)){
    cout << "VOLVER";
    fflush(stdin);
    return;
    }
}


}
}

void submenu_recaudaciones (char *us){      ///LISTO
fflush(stdin);
system("cls");
COORD click;

while (true){
system("cls");
gotoXY(50,0); cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(25,7);cout << "TOTALES";
recuadro(22,10,30,3);
gotoXY(30,12);cout << "POR PELICULA";
recuadro(22,15,30,3);
gotoXY(30,17);cout << "POR CLIENTE";
recuadro(22,20,30,3);
gotoXY(30,22);cout << "POR ADMIN";
gotoXY(25,25);cout <<"*********************";
recuadro(22,27,30,3);
gotoXY(32,29);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){     ///recaudado total
    recau_total();
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,10,13)){     ///x pelicula
    recau_xpel();
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,15,18)){     ///x cliente
    recau_xcl();
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,20,23)){     ///x admin
    recau_xadmin();
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,27,30)){
    cout << "VOLVER";
    fflush(stdin);
    return;

}
}


}

}

void submenu_nav_pel (char *us){    ///LISTO
COORD click;
fflush(stdin);

while (true){
system("cls");
gotoXY(50,0); cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(35,7);cout << "TODAS";
recuadro(22,10,30,3);
gotoXY(32,12);cout << "POR NOMBRE";
recuadro(22,15,30,3);
gotoXY(32,17);cout << "POR GENERO";
gotoXY(25,20);cout <<"*********************";
recuadro(22,22,30,3);
gotoXY(32,24);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    listarpeliculas();
    fflush(stdin);
    break;
}else if (clikeo(click,10,13)){
    listar_pel_xnom();
    fflush(stdin);
    break;
}else if (clikeo(click,15,18)){
    listar_pel_xgenero();
    fflush(stdin);
    break;
}else if (clikeo(click,22,25)){
    cout << "VOLVER";
    fflush(stdin);
    return;
    }
}

}

}

void submenu_bkp_real (char *us){
fflush(stdin);
system("cls");
COORD click;
string ruta,destino;

while (true){
system("cls");
gotoXY(50,0); cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(25,7);cout << "REALIZAR BACKUP DIRECTORES";
recuadro(22,10,30,3);
gotoXY(25,12);cout << "REALIZAR BACKUP PELICULAS";
recuadro(22,15,30,3);
gotoXY(25,17);cout << "REALIZAR BACKUP ADMINS";
recuadro(22,20,30,3);
gotoXY(25,22);cout << "REALIZAR BACKUP VENTAS";
recuadro(22,25,30,3);
gotoXY(25,27);cout << "REALIZAR BACKUP CLIENTES";
recuadro(22,30,30,3);
gotoXY(25,32);cout << "REALIZAR BACKUP ALQUILERES";
recuadro(22,35,30,3);
gotoXY(30,37);cout << "REALIZAR TODO";
gotoXY(25,40);cout <<"*********************";
recuadro(22,41,30,3);
gotoXY(32,43);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    ruta="directores.dat";
    destino="directores.bkp";
    copy_file(ruta,destino);
    fflush(stdin);
    break;
}else if (clikeo(click,10,13)){
    ruta="peliculas.dat";
    destino="peliculas.bkp";
    copy_file(ruta,destino);
    fflush(stdin);
    break;
}else if (clikeo(click,15,18)){
    ruta="admins.dat";
    destino="admins.bkp";
    copy_file(ruta,destino);
    fflush(stdin);
    break;
}else if (clikeo(click,20,23)){
    ruta="ventas.dat";
    destino="ventas.bkp";
    copy_file(ruta,destino);
    fflush(stdin);
    break;
}else if (clikeo(click,25,28)){
    ruta="clientes.dat";
    destino="clientes.bkp";
    copy_file(ruta,destino);
    fflush(stdin);
    break;
}else if (clikeo(click,30,33)){
    ruta="alquileres.dat";
    destino="alquileres.bkp";
    copy_file(ruta,destino);
    fflush(stdin);
    break;
}else if (clikeo(click,35,38)){
   bkp_todo();
    fflush(stdin);
    break;
}else if (clikeo(click,41,44)){
    cout << "VOLVER";
    fflush(stdin);
    return;
    }
}


}



}


void menu_config (char *us){
fflush(stdin);
system("cls");
COORD click;

while (true){
system("cls");
gotoXY(50,0); cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(22,5,30,3);
gotoXY(30,7);cout << "REALIZAR BACKUP";
recuadro(22,10,30,3);
gotoXY(30,12);cout << "RESTAURAR BACKUP";
gotoXY(25,15);cout <<"*********************";
recuadro(22,16,30,3);
gotoXY(32,18);cout << "VOLVER";
cout<<endl<<endl<<endl;

while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    fflush(stdin);
    submenu_bkp_real(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,10,13)){
    fflush(stdin);
    submenu_bkp_rest(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,16,19)){
    cout << "VOLVER";
    fflush(stdin);
    return;
    }
}


}


}

void menu_ventas (char *us){
fflush(stdin);
system("cls");
COORD click;

while (true){
    gotoXY(50,0);cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(25,5,25,3);
gotoXY(30,7);cout << "LISTAR TODAS";
recuadro(25,10,25,3);
gotoXY(30,12);cout << "LISTAR POR ID";
recuadro(25,15,25,3);
gotoXY(27,17);cout << "LISTAR POR CLIENTE";
recuadro(25,20,25,3);
gotoXY(30,22);cout << "LISTAR POR PELICULA";
recuadro(25,25,25,3);
gotoXY(30,27);cout << "LISTAR POR DIRECTOR";
gotoXY(25,32);cout <<"*********************";
recuadro(25,34,25,3);
gotoXY(32,36);cout << "VOLVER";
cout<<endl<<endl<<endl;



while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){
    listar_ven();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,10,13)){
    listar_ven_xid();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,15,18)){
    listar_ven_xcl();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,20,23)){
   listar_ven_xpel();
   fflush(stdin);
   system("cls");
    break;
} else if (clikeo(click,25,28)){
    listar_ven_xdir();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,34,39)){
    cout << "VOLVER" <<endl;
    fflush(stdin);
    return;
}


}

}
system("cls");
}

void menu_reportes (char *us) {
fflush(stdin);
system("cls");
COORD click;

while (true){
    gotoXY(50,0);cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(25,5,25,3);
gotoXY(30,7);cout << "RECAUDACIONES";
recuadro(25,10,25,3);
gotoXY(30,12);cout << "PELI MAS VENDIDA";
recuadro(25,15,25,3);
gotoXY(29,17);cout << "PELI MENOS VENDIDA";
recuadro(25,20,25,3);
gotoXY(30,22);cout << "PELI POR CLIENTE";
gotoXY(25,25);cout <<"*********************";
recuadro(25,27,25,3);
gotoXY(35,29);cout << "VOLVER";
cout<<endl<<endl<<endl;



while (true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,5,8)){     ///RECAUDACIONES
    submenu_recaudaciones(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,10,13)){
    pel_mas_ven();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,15,18)){
    pel_menos_ven();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,20,23)){
    listar_pel_xcl();
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,27,30)){
    cout << "VOLVER" <<endl;
    fflush(stdin);
    return;
}


}

}
system("cls");
}


void menu_administrador (char *us){
system("cls");
fflush(stdin);
COORD click;

while (true){
gotoXY(50,0);cout << "Usuario";
gotoXY(50,1);cout << us;
recuadro(25,0,20,3);
gotoXY(30,2);cout << "DIRECTORES";          ///listo
recuadro(25,5,20,3);
gotoXY(30,7);cout << "PELICULAS";           ///listo
recuadro(25,10,20,3);
gotoXY(31,12);cout << "USUARIOS";           ///lsito
recuadro(25,15,20,3);
gotoXY(29,17);cout << "TRANSACCIONES";      ///listo
recuadro(25,20,20,3);
gotoXY(31,22);cout << "REPORTES";       ///listo
recuadro(25,25,20,3);
gotoXY(30,27);cout << "CONFIGURACION";          ///listo
gotoXY(25,30);cout <<"*********************";
recuadro(25,32,20,3);
gotoXY(32,34);cout << "VOLVER";
cout<<endl<<endl<<endl;



while (true){
    fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,0,3)){
    cout << "directores" <<endl;
    fflush(stdin);
    menudirectores(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,5,8)){
    fflush(stdin);
    menupeliculas(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,10,13)){
    cout << "usuarios" <<endl;
    fflush(stdin);
    menu_usuarios(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,15,18)){
    fflush(stdin);
    menu_ventas(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,20,23)){
    fflush(stdin);
    menu_reportes(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,25,28)){
    fflush(stdin);
    menu_config(us);
    fflush(stdin);
    system("cls");
    break;
} else if (clikeo(click,32,35)){
    cout << "volver" <<endl;
    return;

}

}

}

}

void menu_cliente (char *us) {
COORD click;
fflush(stdin);
system("cls");

while (true){
gotoXY(10,0);cout << "Usuario";
gotoXY(10,1);cout << us;
recuadro(25,0,20,3);
gotoXY(28,2);cout << "NAVEGAR PELICULAS";
recuadro(25,5,20,3);
gotoXY(28,7);cout << "COMPRAR PELICULA";
recuadro(25,10,20,3);
gotoXY(28,12);cout << "ALQUILAR PELICULA";
recuadro(25,15,20,4);
gotoXY(27,17);cout << "LISTAR PELICULAS";
gotoXY(30,18);cout << "ADQUIRIDAS";
recuadro(25,21,20,3);
gotoXY(30,23);cout << "DARSE DE BAJA";
recuadro(25,26,20,3);
gotoXY(30,28);cout << "RENOVAR CUENTA";
gotoXY(25,31);cout <<"*********************";
recuadro(25,33,20,3);
gotoXY(32,35);cout << "VOLVER";
cout<<endl<<endl<<endl;

while(true){
fflush(stdin);
Sleep(100);
click=Mouse();

if (clikeo(click,0,3)){
    fflush(stdin);
    submenu_nav_pel(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,5,8)){
    fflush(stdin);
    compra(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,10,13)){
    fflush(stdin);
    alquila(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,15,19)){
    fflush(stdin);
    listar_pelis_obt(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,21,24)){
    fflush(stdin);
    darse_baja(us);
    fflush(stdin);
    return;
    system("cls");
    break;
}else if (clikeo(click,26,29)){
    fflush(stdin);
    renovar(us);
    fflush(stdin);
    system("cls");
    break;
}else if (clikeo(click,33,36)){
    cout << "Volver";
    system("cls");
    fflush(stdin);
    return;
}



}
}


}

void pantalla_salida() {
system("cls");

gotoXY(30,3);cout << "GRACIAS POR USAR ";
gotoXY(32,4);cout << "BLACKBOSTER";
cout << endl;
exit(0);

}



void menuprincipal() {
textcolor(cVERDE);
char u[20], c[20], l;
string pass="";
int a;
admin ad;
cliente cl;

while (true){
gotoXY(30,3);cout << "BIENVENIDO A ";
gotoXY(32,4);cout << "BLACKBOSTER";
gotoXY(35,5);cout << ":D";

gotoXY(30,10);cout << "---Ingrese su usuario---";
gotoXY(32,12); cout <<"-o un 0 para salir-";
gotoXY(30,15);cin.getline(u,20);
if(u[0]=='0') pantalla_salida();

a=valid_user(u);

    if (a==1){
    do{
    gotoXY(30,17); cout << "                  ";
    gotoXY(30,17); cout << "Ingrese su clave";
    gotoXY(30,19); cout << "                  ";
    gotoXY(30,19); cin.getline (c,20);

/**l=_getch();
    while (l!=13){
        pass.push_back(l);
        cout << "*";
        l=_getch();
    }
    strcpy(c,pass.c_str());
**/
        if (valid_clave(c,u,"admins.dat",ad)){
        menu_administrador(u);
        ///pass="";
        system("cls");
        textcolor(cVERDE);
        }else {
        ///gotoXY(30,19);cout << "                 ";
        }


        }while(!valid_clave(c,u,"admins.dat",ad));



    }else if (a==2){
     do{
    gotoXY(30,17); cout << "                  ";
    gotoXY(30,17); cout << "Ingrese su clave";
    gotoXY(30,19); cout << "                  ";
    gotoXY(30,19); cin.getline(c,20);

        if (valid_clave(c,u,"clientes.dat",cl)){
        menu_cliente(u);
        system("cls");
        textcolor(cVERDE);
        }else {
        ///gotoXY(30,19);cout << "                 ";

        }
        }while(!valid_clave(c,u,"clientes.dat",cl));


    }else if (a==0){
    gotoXY(30,21);cout << "Usuario Incorrecto ";
    gotoXY(30,15);cout << "                    ";

    }


}
}


#endif // MENUES_H_INCLUDED
