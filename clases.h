#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

template <class temp>
void pedirdato (temp *n){
cin >> *n;
while (true){
    if (cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "caracter incorrecto" << endl;
    cin >> *n;
    }else {
    break;
    }
}

}

template <class temp>
float val_transaccion (temp def , char *direccion, int idpeli=-10 , int idadmin=-10 , int idcliente =-10){
float val_acum=0;
FILE *p=fopen(direccion,"rb");
if (p==NULL) {
    return 0;
}

while (fread(&def,sizeof(def),1,p)==1){
    if (idpeli!=-10){
    if (idpeli==def.getidpeli()){
    val_acum+=def.getimporte();
    continue;
    }
    }else if (idadmin!=-10){
    if (idadmin==def.getidadmin()){
    val_acum+=def.getimporte();
    continue;
    }
    }else if (idcliente!=-10){
    if (idcliente==def.getidcliente()){
    val_acum+=def.getimporte();
    continue;
    }
    }else {
    val_acum+=def.getimporte();
    continue;}
}
fclose(p);

return val_acum;

}


template <class temp>
int autonumerar (temp clase , char *direccion){
FILE *p;
int res;
p=fopen(direccion , "rb");
if (p==NULL) return 1;

fseek(p,sizeof (clase),2);
res=ftell(p)/sizeof(clase);
fclose(p);
return res;
}

template <class temp>
bool validar_exist (temp nuevo , char *direccion){
FILE *p;
temp viejo;
p=fopen(direccion , "rb");
if (p==NULL) return false;

while (fread(&viejo ,sizeof viejo , 1 , p)==1){
   if (nuevo==viejo){
    fclose(p);
    cout << "Registro ya existente , ingrese nuevamente" << endl;
    return true;
   }

}
fclose(p);
return false;

}




class fecha {
private:
int dia, mes , anio ;

public :
bool aniobisiesto (int a) {
if (a%4==0) {return true;
}else {return false;}
}

int calcular_dias_mes(int m, bool b){
int cantdias;

  if (m==1||m==3||m==5||m==7||m==8||m==10||m==12){
    cantdias=31;

  }else if(m==4||m==6||m==9||m==11){cantdias=30;
  }else if (m==2) {
    if (b){
        cantdias=29;
    }else {cantdias=28;}
  }



return cantdias;
}


int getdia () {return dia;}
int getmes () {return mes;}
int getanio () {return anio;}

void setSinFecha() {
dia=0;
mes=0;
anio=0;
}

bool setfecha (int d , int m , int a) {

bool b;
int cantdias;

time_t tiempo;
struct tm *actual;

tiempo=time(NULL);
actual= localtime(&tiempo);


if (a<=actual->tm_year+1900) {
    b= aniobisiesto(a);
if (m>0 && m<13){
    cantdias=calcular_dias_mes(m,b);
    if (d>=1 && d<=cantdias){

    dia=d;
    mes=m;
    anio=a;

    return true;

    }else {
        cout <<"Error en dia"<<endl;
        return false;}
  }else {
      cout << "Error en mes"<<endl;
      return false;}
}else {
    cout << "Error en anio"<<endl;
    return false;}

}


bool operator == (fecha aux){

if (aux.getdia()==dia &&  aux.getmes()==mes && aux.getanio()== anio){
    return true;
}
return false;
}

void operator + (int dias){
bool b, a=false;
int diasm;

b=aniobisiesto(anio);
diasm=calcular_dias_mes(mes,b);
diasm-=dia;

while (dias>diasm){
    a=true;
    if (mes==12){
        dias-=diasm;
        anio+=1;
        mes=1;
        b=aniobisiesto(anio);
        diasm=calcular_dias_mes(mes,b);
    }else{
    mes+=1;
    dias-=diasm;
    diasm=calcular_dias_mes(mes,b);
    }
}
if (a){
dia=dias;
}else {
dia+=dias;
}
}

void mostrar_fecha(){
cout << dia << "/"<<mes <<"/"<<anio;
}
};


class director {
private:
char nombre[30], apellido [30];
int iddir , edad ;
fecha fechanac;
bool estado;

public:

bool setfechanac (int d , int m , int a) {
    bool respuesta;
    respuesta=fechanac.setfecha(d,m,a);
    return respuesta;}
int getdia () {return fechanac.getdia();}
int getmes () {return fechanac.getmes();}
int getanio () {return fechanac.getanio();}
void setnombre (char n[30]){strcpy(nombre,n);}
void setapellido (char n[30]){strcpy(apellido,n);}
void setiddir (int id) {iddir=id;}
void setedad (int ed) {edad=ed;}
void setestado (bool e) {estado=e;}
char *getnombre () {return nombre;}
char *getapellido () {return apellido;}
int getid () {return iddir;}
int getedad () {return edad;}
bool getestado () {return estado;}
fecha getfecha () {return fechanac;}

void calcularedad () {
time_t tiempo;
struct tm *actual;
int a;

tiempo=time(NULL);
actual= localtime(&tiempo);

a=fechanac.getanio();

edad= (1900+actual->tm_year) - a;

system("pause");

if(fechanac.getmes()>(actual->tm_mon+1) ){
    edad-=1;
}else if (fechanac.getmes()==(actual->tm_mon+1) ){
    if (fechanac.getdia()>actual->tm_mday){
    edad-=1;
}
}

}

void pedir_director(){
int d , m, a;
bool valido=true , b;
director dir;
iddir=autonumerar(dir,"directores.dat");

cout << "INGRESE NOMBRE: ";cin.getline(nombre,30);

cout << "INGRESE APELLIDO ";cin.getline (apellido,30);
do{
cout << "INGRESE SU FECHA DE NACIMIENTO: " << endl << "DIA: ";pedirdato(&d);
cout << "MES: ";pedirdato(&m);
cout << "ANIO: ";pedirdato(&a);
while(!fechanac.setfecha(d,m,a)){

 cout << "valores incorrectos , ingrese de vuelta en mismo orden" << endl;
 pedirdato(&d);
 pedirdato(&m);
 pedirdato(&a);

}
calcularedad();
if (edad >=18 && edad <=100){
    b=false;
}else {b=true;
    cout << "Edad incorrecta" << endl << endl;
    }

}while(b);


estado=true;


}

bool operator == (director aux){

    if (aux.getedad()==edad && strcmp(aux.getapellido(),apellido)==0 && strcmp(aux.getnombre(),nombre)==0){
      if (aux.getfecha()==fechanac){
return true;
}}
return false;
}


};

class pelicula {
private:

int idpeli, iddir , idadmin;
float p_venta , p_alquiler, duracion;
char nombre[30] , genero[30];
bool estado;

public:
void setidadmin (int id) {idadmin=id;}
int getidadmin () {return idadmin;}
void setidpeli (int id) {idpeli=id;}
void setiddir (int id) {iddir=id;}
void setduracion (float d) {duracion=d;}
void setp_venta (float p) {p_venta=p;}
void setp_alquieler (float p) {p_alquiler=p;}
void setnombre (char n[30]) {strcpy(nombre,n);}
void setgenero (char g[30]) {strcpy(genero,g);}
void setestado (bool e) {estado=e;}
int getid () {return idpeli;}
int getiddir () {return iddir;}
int getduracion () {return duracion;}
float getp_venta () {return p_venta;}
float getp_alquiler () {return p_alquiler;}
bool getestado () {return estado;}
char *getnombre () {return nombre;}
char *getgenero () {return genero;}
bool operator == (pelicula aux){

if (aux.getduracion()==duracion && aux.getiddir()==iddir){
  if (aux.p_venta==p_venta && aux.p_alquiler==p_alquiler){
  if (strcmp(aux.getgenero(),genero)==0 && strcmp(aux.getnombre(),nombre)==0){
  return true;
}
}
}
return false;

}

bool vali_iddir () {
FILE *p=fopen("directores.dat","rb");
if (p==NULL){
    cout << "ERROR EN DIRECTORES" << endl;
    return false;
}

director dir;
while (fread(&dir,sizeof (director),1,p)==1){
    if (dir.getestado() && dir.getid()==iddir){
    fclose(p);
    return true;
    }
}

fclose(p);
return false;
}

void pedir_pel () {
cout << endl;
cout << "Nombre: "; cin.getline(nombre,30);
cin.ignore();
cout << "Genero: ";cin.getline (genero,30);
cin.ignore();
cout << "Duracion: "; cin >> duracion;
cout << "Precio de venta: "; cin >> p_venta;
cout << "Precio de alquiler: "; cin >> p_alquiler;
cout << "ID de director: "; cin >> iddir;
while (!vali_iddir()){
cout << "ID inexistente o borrado" << endl;
cout << "Introdusca nueva ID : ";
cin >> iddir;
}
estado=true;
}
};

class transaccion {
protected:
float importe;
bool estado;
int idpeli,idcliente , idadmin;

public:
void setimporte (float i) {importe=i;}
void setestado (bool e) {estado=e;}
float getimporte () {return importe;}
bool getestado () {return estado;}
int getidadmin () {return idadmin;}
int getidpeli () {return idpeli;}
int getidcliente () {return idcliente;}
void setidpeli (int i) {idpeli =i;}
void setidadmin (int i) {idadmin =i;}
void setidcliente (int i) {idcliente=i;}

void mostrar_tran() {
cout << endl << "Importe: " << importe<<endl;
cout << "ID de pelicula: "<<idpeli <<endl;
cout << "ID de cliente: "<< idcliente<<endl;
cout << "ID de administrador: "<< idadmin<<endl;
}

};


class alquiler : public transaccion {
private:
int idalquiler, dias;
fecha fech_inicio, fech_final;
bool vencido;

public:
void setidalquiler(int id){idalquiler=id;}
int getidalquiler () {return idalquiler;}
void setdias (int d) {dias=d;}
int getdias () {return dias;}
bool setfecha_inicio (int d, int m, int a){
bool b;
b=fech_inicio.setfecha(d,m,a);
return b;
}
void setfecha_final (){
fech_final.setfecha(fech_inicio.getdia(),fech_inicio.getmes(),fech_inicio.getanio());
fech_final+dias;
}

fecha getfecha_inicio (){return fech_inicio;}
fecha getfecha_final () {return fech_final;}
int getdia_inicio () {return fech_inicio.getdia();}
int getmes_inicio () {return fech_inicio.getmes();}
int getanio_inicio () {return fech_inicio.getanio();}
int getdia_final () {return fech_final.getdia();}
int getmes_final () {return fech_final.getmes();}
int getanio_final () {return fech_final.getanio();}
bool getvencimiento () {return vencido;}
void setvencimiento (bool b) {vencido=b;}

void mostrar_alq () {

mostrar_tran();
cout << "ID de alquiler: "<<idalquiler <<endl;
cout << "Dias por los que se alquilo ultima vez:"<< dias<<endl;
cout << "Fecha de adquisicion: "<< fech_inicio.getdia() << "/" << fech_inicio.getmes() << "/" << fech_inicio.getanio()<<endl;
cout << "Fecha de Finalizacion: "<< fech_final.getdia() << "/" << fech_final.getmes() << "/" << fech_final.getanio()<<endl;
}

};

class venta:public transaccion {
private:

int idventa;
fecha fecha_venta;

public:

int getid () {return idventa;}
void setidventa (int i) {idventa=i;}
int getdia () {return fecha_venta.getdia();}
int getmes () {return fecha_venta.getmes();}
int getanio () {return fecha_venta.getanio();}
fecha getfecha () {return fecha_venta;}
bool setfecha (int d , int m, int a) {
    return fecha_venta.setfecha(d,m,a);}

bool operator == (venta aux){

 if (aux.getimporte()==importe && aux.getidcliente()==idcliente && aux.getidpeli()==idpeli ){
 if (aux.getfecha()==fecha_venta){
 return true;

}}
return false;
}

void mostrar_venta () {

mostrar_tran();
cout << "ID de venta: " << idventa << endl;
cout << "Fecha de Venta: "<< fecha_venta.getdia() << "/" << fecha_venta.getmes() << "/" << fecha_venta.getanio()<<endl;

}

};

class usuario {
protected:
char nombre[20];
int idusuario ;
bool estado;
char contrasena [20];

public:
char * getcontrasena () {return contrasena;}
void setcontrasena (char *c) {strcpy(contrasena,c);}
void setidusuario (int i) {idusuario=i;}
void setestado (bool e) {estado=e;}
void setnombre (char n[20]) {strcpy(nombre,n);}
char *getnombre () {return nombre;}
bool getestado () {return estado;}
int getid () {return idusuario;}
void pedir_usuario() {
cout << "Ingrese su nombre de usuario: ";cin.getline(nombre,20);cout<<endl;
cout << "Ingrese la clave a utilizar: ";cin.getline(contrasena,20);cout<< endl;
estado=true;
}
};

 class cliente: public usuario {
private:
int edad , dni;
fecha comienzo , vencimiento;
char apellido[20], mail[30];
int cant_pelis;

public:
fecha getvencimiento () {return vencimiento;}
void sumar_dias (int dias) {vencimiento+dias;}
void setcant_p (int c) {cant_pelis=c;}
int getcant_p () {return cant_pelis;}
void setedad (int e) {edad=e;}
void setapellido (char a[20]) {strcpy(apellido,a);}
void setmail (char a[30]) {strcpy(mail,a);}
char *getapellido () {return apellido;}
char *getmail () {return mail;}
int getedad () {return edad;}
int getdia_comienzo () {return comienzo.getdia();}
int getmes_comienzo () {return comienzo.getmes();}
int getanio_comienzo () {return comienzo.getanio();}
bool setfecha_comienzo (int d , int m, int a) {
    return comienzo.setfecha(d,m,a);}
int getdia_vencimiento () {return vencimiento.getdia();}
int getmes_vencimiento () {return vencimiento.getmes();}
int getanio_vencimiento () {return vencimiento.getanio();}
bool setfecha_vencimiento (int d , int m, int a) {
    return vencimiento.setfecha(d,m,a);}

bool operator == (cliente aux){

if(strcmp(nombre,aux.nombre)==0){

    return true;

}
return false;

}

void mostrar_cliente(){
cout << "ID de cliente: " << idusuario << endl;
cout << "Nombre: " << nombre <<endl;
cout << "Apellido: " << apellido << endl;
cout << "Edad: " << edad << endl;
cout << "DNI: " << dni << endl;
cout << "Correo: " << mail << endl;
cout << "Dia de Inscripcion: ";comienzo.mostrar_fecha();cout << endl;
cout << "Finaliza su inscripcion el dia: ";vencimiento.mostrar_fecha();cout << endl;

}

void pedir_cliente (){
time_t tiempo;
struct tm *actual;
int dias;
bool b;

tiempo=time(NULL);
actual= localtime(&tiempo);

pedir_usuario();

cout << "Apellido: ";
cin.getline(apellido,20);

cout << "DNI: ";
pedirdato(&dni);
cout << "Edad: ";
pedirdato(&edad);

cout << "Correo: ";
cin >> mail;

cant_pelis=0;

comienzo.setfecha(actual->tm_mday,actual->tm_mon+1,actual->tm_year+1900);
vencimiento.setfecha(actual->tm_mday,actual->tm_mon+1,actual->tm_year+1900);

cout << "Cantidad de dias a subscribirse: "; pedirdato(&dias);

vencimiento+dias;

}

};

class admin: public usuario {
private:
int cantclientes , cantpeliculas;
float valor_recaudado;
public:
int getcantclientes () {return cantclientes;}
int getcantpeliculas () {return cantpeliculas;}
float getvalor_recaudado () {return valor_recaudado;}
void setcantclientes (int c) {cantclientes=c;}
void setcantpeliculas (int c) {cantpeliculas=c;}
void setvalor_recaudado (float v) {valor_recaudado=v;}
bool operator == (admin ad){

if (strcmp(nombre,ad.getnombre())==0){
return true;

return false;
}}

void pedir_admin () {
admin ad;

pedir_usuario();
idusuario=autonumerar(ad,"admins.dat")-1;
cantclientes=0;
cantpeliculas=0;
valor_recaudado=0;
}

void mostrar_admin () {

cout << "ID de Administrador: " << idusuario << endl;
cout << "Nombre: " << nombre << endl;
cout << "Cantidad de clientes agregados: " << cantclientes << endl;
cout << "Cantidad de peliculas agregadas: " << cantpeliculas << endl;
cout << "Importe recuadado por sus peliculas: " << valor_recaudado << endl;
}

};


#endif // CLASES_H_INCLUDED
