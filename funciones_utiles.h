#ifndef FUNCIONES_UTILES_H_INCLUDED
#define FUNCIONES_UTILES_H_INCLUDED

bool check_fecha (fecha fech){
time_t tiempo;
struct tm *actual;

tiempo=time(NULL);
actual= localtime(&tiempo);


if (fech.getanio() > actual->tm_year+1900){
    return true;}
if (fech.getanio() == actual->tm_year+1900){
    if (fech.getmes() > actual->tm_mon+1){
        return true;}
    if (fech.getmes() == actual->tm_mon+1){
        if (fech.getdia() >= actual->tm_mday){
            return true;
        }else {return false;}
    }else {return false;}
}else {return false;}

}


template <class temp>
int contar_reg(temp obj, char *direccion) {
FILE *p;
int res=0;

p=fopen(direccion,"rb");
if (p==NULL){
    return 0;
}

fseek(p,0,SEEK_END);
res=ftell(p)/sizeof(obj);

fclose(p);

return res;

}

bool val_vencido_cl(int pos){
cliente cl;
FILE *p=fopen("clientes.dat","rb");
if (p==NULL){
    return 0;
}

fseek(p,pos*sizeof(cliente),0);
fread(&cl,sizeof(cliente),1,p);

if (check_fecha(cl.getvencimiento())==false && cl.getestado()==true){
fclose(p);
return true;
}
fclose(p);
return false;
}


void vencer_cl(int pos){
cliente cl;
FILE *p=fopen("clientes.dat","rb+");
if (p==NULL){
    return;
}

fseek(p,pos*sizeof(cliente),0);
fread(&cl,sizeof(cliente),1,p);
cl.setestado(false);

fseek(p,ftell(p)-sizeof(cliente),0);
fwrite(&cl,sizeof(cliente),1,p);

fclose(p);
return;
}

void check_cl () {
cliente cl;
int cant=0;

cant=contar_reg(cl,"clientes.dat");
if (cant==0) return;

for (int pos=0; pos<=cant; pos++){
    if (val_vencido_cl(pos)){
    vencer_cl(pos);
    }
}

return;
}

bool val_vencido_alq(int pos){
alquiler alq;
FILE *p=fopen("alquileres.dat","rb");
if (p==NULL){
    return 0;
}

fseek(p,pos*sizeof(alquiler),0);
fread(&alq,sizeof(alquiler),1,p);

if (check_fecha(alq.getfecha_final())==false && alq.getestado()==true){
fclose(p);
return true;
}
fclose(p);
return false;
}

void vencer_alq(int pos){
alquiler alq;
FILE *p=fopen("alquileres.dat","rb+");
if (p==NULL){
    return;
}

fseek(p,pos*sizeof(alquiler),0);
fread(&alq,sizeof(alquiler),1,p);
alq.setvencimiento(true);

fseek(p,ftell(p)-sizeof(alquiler),0);
fwrite(&alq,sizeof(alquiler),1,p);

fclose(p);
return;
}

void check_alq(){
int cant=0;
alquiler alq;

cant=contar_reg(alq,"alquileres.dat");
if (cant==0) return;

for (int pos=0; pos<=cant; pos++){
    if (val_vencido_alq(pos)){
    vencer_alq(pos);
    }
}

return;
}




void copy_file(string ruta, string destino){
 FILE * archivo;
 string cadena;
 if (archivo = fopen(ruta.c_str(), "r"))
 {
  cadena = "copy " + ruta + " " + destino;
  system(cadena.c_str());
  fclose(archivo);
 }
 else
 {
   cout << "El archivo no existe " << endl;
 }
}

void rest_todo (){
string ruta, destino;

    ruta="directores.bkp";
    destino="directores.dat";
    copy_file(ruta,destino);
    ruta="peliculas.bkp";
    destino="peliculas.dat";
    copy_file(ruta,destino);
    ruta="admins.bkp";
    destino="admins.dat";
    copy_file(ruta,destino);
    ruta="ventas.bkp";
    destino="ventas.dat";
    copy_file(ruta,destino);
    ruta="clientes.bkp";
    destino="clientes.dat";
    copy_file(ruta,destino);
    ruta="alquileres.bkp";
    destino="alquileres.dat";
    copy_file(ruta,destino);
}

void poner_en_cero (int *v , int tam){
int i;
for (i=0;i<tam;i++){
    v[i]=0;
}

}

void bkp_todo (){
string ruta, destino;

    ruta="directores.dat";
    destino="directores.bkp";
    copy_file(ruta,destino);
    ruta="peliculas.dat";
    destino="peliculas.bkp";
    copy_file(ruta,destino);
    ruta="admins.dat";
    destino="admins.bkp";
    copy_file(ruta,destino);
    ruta="ventas.dat";
    destino="ventas.bkp";
    copy_file(ruta,destino);
    ruta="clientes.dat";
    destino="clientes.bkp";
    copy_file(ruta,destino);
    ruta="alquileres.dat";
    destino="alquileres.bkp";
    copy_file(ruta,destino);
}



int buscar_id_admin (char *us){
FILE *p=fopen("admins.dat","rb");
if (p==NULL) return -10;
admin ad;
int id;

while (fread(&ad,sizeof(admin),1,p)==1){
    if (strcmp(ad.getnombre(),us)==0){
     id=ad.getid();
     fclose(p);
     return id;
    }
}

}


void gotoXY(int x, int y){
	 COORD coord = {x, y};

	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	 return;
}


bool admin_check(){
FILE *p=fopen("admins.dat","rb");
if (p==NULL) {return false;}
admin user;

if (fread(&user,sizeof(admin),1,p)==1){
return true;
}

return false;
}

void crear_admin(){
admin ad;
FILE *p=fopen("admins.dat","ab");
//if (p==NULL) exit(-1);

ad.setidusuario(0);
ad.setcantclientes(0);
ad.setcantpeliculas(0);
ad.setcontrasena("123");
ad.setestado(true);
ad.setnombre("Administrador");
ad.setvalor_recaudado(0);

fwrite(&ad,sizeof (admin),1,p);

fclose(p);
}


int valid_user(char *u){
FILE *p=fopen("admins.dat","rb");
if (p==NULL) exit(-1);
admin ad;

while (fread(&ad,sizeof (admin) , 1, p)==1){
    if (strcmp(u,ad.getnombre())==0 && ad.getestado()){
    fclose(p);
    return 1;
    }
}
fclose(p);
p=NULL;


cliente cl;
p=fopen("clientes.dat","rb");
if (p==NULL) return 0;


while (fread(&cl,sizeof (cliente),1,p)==1){
    if (strcmp(u,cl.getnombre())==0 && cl.getestado()){
    fclose(p);
    return 2;
    }
}

fclose(p);
return 0;

}

template <class temp>
bool valid_clave (char *c , char *u, char *direccion , temp def){
FILE *p=fopen(direccion,"rb");
if (p==NULL)exit(-1);

while(fread(&def,sizeof(temp),1,p)==1){
    if(strcmp(c,def.getcontrasena())==0 && strcmp(u,def.getnombre())==0){

    fclose(p);
    return true;
    }
}
fclose(p);
return false;

}

#endif // FUNCIONES_UTILES_H_INCLUDED
