#include <iostream>
#include <windows.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <wctype.h>
#include <ctime>
#include <conio.h>
#include <limits>

using namespace std;



#include "clases.h"
#include "funciones_utiles.h"
#include "directores.h"
#include "usuarios.h"
#include "peliculas.h"
#include "ventas.h"
#include "clientes.h"
#include "reportes.h"
#include "menues.h"




int main(){

check_alq();
check_cl();

if (admin_check()==false){
   crear_admin();
}
menuprincipal();
return 0;
}
