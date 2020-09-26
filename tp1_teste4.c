//gcc tp1_teste4.c -o tp4 -D FREEGLUT_STATIC -lSOIL -lfreeglut_static -lopengl32 -lwinmm -lgdi32 -Wl,--subsystem,windows

#include <stdio.h>
#include <SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
struct ponto {

    float x, y;
};
struct tamanho {

    float largura, altura;
};
//{/*/coisas/*/}
  struct ponto posicao_Objeto_1;
  struct tamanho tamanho_Objeto_1;
  struct ponto posicao_objeto_caindo[1000];
  struct tamanho tamanho_objeto_caindo;
  int fundo_altura=500;
  int fundo_largura=500;
  GLuint TexturaBicho;
  GLuint TexturaChao;
  GLuint TexturaBranca;
  GLuint TexturaGameOver;
  GLuint TexturaTelaInicial;
  GLuint TexturaFundo;
  int tecla_R_pressionada = 0;
  int tela_tamanho;
  int isLeftKeyPressed;
  int isRightKeyPressed;
  float quanto_cai;
  int quantos_caem=1;
  int tick=0;
  int TelaInicial=1;
  int segundos;
  int colision_reference;
  int vidas =3;
  float progressao;
  float bonus_queda[1000];
  float hearts_side = 15;
  float hearts_side_2 =20;
  int pause_reference=0;
 
//{for do fundo};
int rdm_flt(int a,int b){
  int random;
  random=a+rand()%b;
  return random;
}
void cor(float a,float b,float c){

  glColor3f(a/255,b/255,c/255);
}
void cor_fundo_limpar(float a,float b,float c){
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(a, b, c, 0);
}
void dar_valor_inicial_para_variaveis(){
  isLeftKeyPressed = 0;
  isRightKeyPressed = 0;
  tamanho_Objeto_1.altura = 32;
  tamanho_Objeto_1.largura = 32;
  tamanho_objeto_caindo.altura=8;
  tamanho_objeto_caindo.largura=8;
  quanto_cai=1;
  //progressao = -210;
  segundos=0;
  tela_tamanho = 500;
  colision_reference =0;
  int i ;
  for(i=0;i<1000;i++){
    posicao_objeto_caindo[i].x= (float)rdm_flt(-246,496);
    posicao_objeto_caindo[i].y= (float)rdm_flt(250,200);
    bonus_queda[i]= (((float)rdm_flt(0,50))/100);
  }
  posicao_Objeto_1.y = -199;
  posicao_Objeto_1.x =0;
}
void reiniciar(){
  cor_fundo_limpar(0,0,0);
  dar_valor_inicial_para_variaveis();
}
void inicializa(void){
  cor_fundo_limpar(0,0,0);
  dar_valor_inicial_para_variaveis();
  TexturaBicho = SOIL_load_OGL_texture("creature1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
  TexturaChao = SOIL_load_OGL_texture("bar1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
  TexturaBranca =SOIL_load_OGL_texture("branco.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
  TexturaGameOver =SOIL_load_OGL_texture("gameover.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
  TexturaTelaInicial =SOIL_load_OGL_texture("telainicial1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
  TexturaFundo= SOIL_load_OGL_texture("FUNDO_DESISTO.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
  glEnable(GL_BLEND);
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
void redimensiona(int w, int h){
   glViewport(0, 0, 500, 500);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-(tela_tamanho/2),(tela_tamanho/2), -(tela_tamanho/2),(tela_tamanho/2), -3, 3);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
void teclado(unsigned char key, int x, int y){
   switch(key){
       case 32:
        TelaInicial=0;
        break;
      case 27:
         exit(0);
         break; 
      case 'a':
      case 'A':
        if (isRightKeyPressed == 0) {
          isLeftKeyPressed = 1;
        }
        break;
      case 'd':
      case 'D':
        if (isLeftKeyPressed == 0) {
          isRightKeyPressed = 1;
        }
        break;
      case 'r':
        tecla_R_pressionada++;
        if(tecla_R_pressionada == 2){
          tecla_R_pressionada = 0;
          //fazer coisas para reiniciar;
          reiniciar();
          vidas =3;
          quantos_caem=1;
        }
        break;
      case'p':
      case'P':
        if(pause_reference==1){
          pause_reference=0;
        }
        if(pause_reference==0){
          pause_reference=1;
        }
        break;
      case 's':
      quantos_caem++;
      default:
         break;
      }
}
void movimenta_criatura(){
  if(isLeftKeyPressed == 1 && posicao_Objeto_1.x - 1 > -1*((tela_tamanho/2)-(tamanho_Objeto_1.largura/2))){//(242 é o tamanho da tela menos metade mais ou menos do carinha é provisorio.)
    posicao_Objeto_1.x -= 1;
  }
  if(isRightKeyPressed == 1 && posicao_Objeto_1.x + 1 < ((tela_tamanho/2)-(tamanho_Objeto_1.largura/2))){
    posicao_Objeto_1.x += 1.5;
  }
}
void acelera(int i){
    if(posicao_objeto_caindo[i].y < 50 ){
      quanto_cai+= 0.000001;
    }
     if(posicao_objeto_caindo[i].y < 0 ){
      quanto_cai+= 0.000001;
    }
     if(posicao_objeto_caindo[i].y< -210){
      quanto_cai+= 0.000001;
    } 
}
void colision(int i){
  if( (posicao_Objeto_1.x - tamanho_Objeto_1.largura/2)  < posicao_objeto_caindo[i].x && posicao_objeto_caindo[i].x < (posicao_Objeto_1.x + tamanho_Objeto_1.largura/2) ){
    if((posicao_Objeto_1.y - tamanho_Objeto_1.altura/2) < posicao_objeto_caindo[i].y && posicao_objeto_caindo[i].y < (tamanho_Objeto_1.altura/2 + posicao_Objeto_1.y)){
        colision_reference++;
        posicao_objeto_caindo[i].y =300;
        posicao_objeto_caindo[i].x = (float) rdm_flt(-246,496);
        vidas--;
        reiniciar();
    }
  }
  if(colision_reference==1){
    colision_reference=0;
  }
}
void cai_coisas(){
  int i;
  for(i=0;i<quantos_caem;i++){
    posicao_objeto_caindo[i].y = posicao_objeto_caindo[i].y - (quanto_cai + bonus_queda[i]);
     acelera(i);
     colision(i);
    if(posicao_objeto_caindo[i].y < rdm_flt(-290,80)){
      posicao_objeto_caindo[i].y = rdm_flt(260,40);
      posicao_objeto_caindo[i].x = (float) rdm_flt(-246,496);
    }
  }
  if(tick%47 ==0 && segundos%5==0){
    if(quantos_caem!=1000)
        quantos_caem++;
      }
}
void handleSpecialKeyReleased(unsigned char key, int x, int y) {
 switch (key) {
 case 'a':
  isLeftKeyPressed = 0;
  break;
 case 'd':
  isRightKeyPressed = 0;
  break;
 }
}
void hearts(float a, float b){
  if(vidas==3){
      glPushMatrix();
      glTranslatef(a,b,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-1*hearts_side,0,1);
        glVertex3f(0,-1*hearts_side,1);
        glVertex3f(hearts_side,0,1);
        glVertex3f((hearts_side/2),hearts_side,1);
        glVertex3f(0,(hearts_side/2),1);
        glVertex3f(-1*(hearts_side/2),hearts_side,1);
      glEnd();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(a - 2*hearts_side_2,b,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-1*hearts_side,0,1);
        glVertex3f(0,-1*hearts_side,1);
        glVertex3f(hearts_side,0,1);
        glVertex3f((hearts_side/2),hearts_side,1);
        glVertex3f(0,(hearts_side/2),1);
        glVertex3f(-1*(hearts_side/2),hearts_side,1);
      glEnd();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(a - 4*hearts_side_2 ,b,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-1*hearts_side,0,1);
        glVertex3f(0,-1*hearts_side,1);
        glVertex3f(hearts_side,0,1);
        glVertex3f((hearts_side/2),hearts_side,1);
        glVertex3f(0,(hearts_side/2),1);
        glVertex3f(-1*(hearts_side/2),hearts_side,1);
      glEnd();
    glPopMatrix();
  }
  if(vidas==2){
       glPushMatrix();
      glTranslatef(a,b,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-1*hearts_side,0,1);
        glVertex3f(0,-1*hearts_side,1);
        glVertex3f(hearts_side,0,1);
        glVertex3f((hearts_side/2),hearts_side,1);
        glVertex3f(0,(hearts_side/2),1);
        glVertex3f(-1*(hearts_side/2),hearts_side,1);
      glEnd();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(a - 2*hearts_side_2,b,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-1*hearts_side,0,1);
        glVertex3f(0,-1*hearts_side,1);
        glVertex3f(hearts_side,0,1);
        glVertex3f((hearts_side/2),hearts_side,1);
        glVertex3f(0,(hearts_side/2),1);
        glVertex3f(-1*(hearts_side/2),hearts_side,1);
      glEnd();
    glPopMatrix();
  }
  if(vidas==1){
      glPushMatrix();
      glTranslatef(a,b,0);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-1*hearts_side,0,1);
        glVertex3f(0,-1*hearts_side,1);
        glVertex3f(hearts_side,0,1);
        glVertex3f((hearts_side/2),hearts_side,1);
        glVertex3f(0,(hearts_side/2),1);
        glVertex3f(-1*(hearts_side/2),hearts_side,1);
      glEnd();
    glPopMatrix();
  }
}
void progression(){
  //-240 a 240, começa em -240. 480 pixels.
  progressao = (tick * 0.017) -240;
}
void atualiza() {
  if(pause_reference==0){
    tick++;
    if(tick%47 == 0){
      segundos++;
    }
    cai_coisas();
    movimenta_criatura();
    glutPostRedisplay();
    progression();
    glutTimerFunc(16, atualiza, 0);
  }
}
void desenhaCena(void){
  int i,j;
  cor_fundo_limpar(0,0,0);

  glClear(GL_COLOR_BUFFER_BIT);

    cor(255,255,255);
     // glEnable(GL_DEPTH_TEST);
  	  glEnable(GL_TEXTURE_2D);

      glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,TexturaFundo);
        glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0, 0); glVertex3f(-1*(fundo_largura/2),-1*(fundo_altura/2),  -2);
          glTexCoord2f(1, 0); glVertex3f((fundo_largura/2), -1*(fundo_altura/2), -2);
          glTexCoord2f(1, 1); glVertex3f((fundo_largura/2),(fundo_altura/2), -2);
          glTexCoord2f(0, 1); glVertex3f(-1*(fundo_largura/2),(fundo_altura/2),-2);
        glEnd();
      glPopMatrix();
    
    cor(255,255,255);
    glPushMatrix();
      glBindTexture(GL_TEXTURE_2D,TexturaBicho);
      glTranslatef(posicao_Objeto_1.x, posicao_Objeto_1.y, 0);

      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(-1*(tamanho_Objeto_1.largura/2),-1*(tamanho_Objeto_1.altura/2),  2);
        glTexCoord2f(1, 0); glVertex3f((tamanho_Objeto_1.largura/2), -1*(tamanho_Objeto_1.altura/2), 2);
        glTexCoord2f(1, 1); glVertex3f((tamanho_Objeto_1.largura/2),(tamanho_Objeto_1.altura/2), 2);
        glTexCoord2f(0, 1); glVertex3f(-1*(tamanho_Objeto_1.largura/2),(tamanho_Objeto_1.altura/2),2);
      glEnd();
    glPopMatrix();

    for(i=0;i<quantos_caem;i++){
        glPushMatrix();
          glBindTexture(GL_TEXTURE_2D,TexturaBranca);
          glTranslatef(posicao_objeto_caindo[i].x,posicao_objeto_caindo[i].y,0);
          glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);glVertex3f(-1*(tamanho_objeto_caindo.largura/2),0,1);
            glTexCoord2f(1, 0);glVertex3f(0,-1*(tamanho_objeto_caindo.altura/2),1);
            glTexCoord2f(1, 1);glVertex3f((tamanho_objeto_caindo.largura/2),0,1);
            glTexCoord2f(0, 1);glVertex3f(0,(tamanho_objeto_caindo.altura/2),1);
          glEnd();
        glPopMatrix();
    }
    hearts(tela_tamanho/2 - hearts_side_2 ,tela_tamanho/2 - hearts_side_2 );
    glPushMatrix();
      glBindTexture(GL_TEXTURE_2D,TexturaChao);

      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(-250,-250,1);
        glTexCoord2f(1, 0); glVertex3f(250, -250 , 1);
        glTexCoord2f(1, 1); glVertex3f(250, -210, 1);
        glTexCoord2f(0, 1); glVertex3f(-250 , -210, 1);
      glEnd();
    glPopMatrix();

    glPushMatrix();
      glBindTexture(GL_TEXTURE_2D,TexturaBranca);

      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(-1*(tela_tamanho/2 - 10 ),-1*(tela_tamanho/2 - 10),1);
        glTexCoord2f(1, 0); glVertex3f( progressao, -1*(tela_tamanho/2 - 10) , 1);
        glTexCoord2f(1, 1); glVertex3f( progressao, -1*(tela_tamanho/2 - 20), 1);
        glTexCoord2f(0, 1); glVertex3f(-1*(tela_tamanho/2 - 10 ) ,-1*(tela_tamanho/2 - 20), 1);
      glEnd();
    glPopMatrix();

      if(vidas<0 || progressao >= 240){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,TexturaGameOver);

        glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0, 0); glVertex3f(-250,-250,3);
          glTexCoord2f(1, 0); glVertex3f(250, -250 , 3);
          glTexCoord2f(1, 1); glVertex3f(250, 250, 3);
          glTexCoord2f(0, 1); glVertex3f(-250 , 250, 3);
        glEnd();
      glPopMatrix();
      }
    if(TelaInicial==1){
      glPushMatrix();
      glBindTexture(GL_TEXTURE_2D,TexturaTelaInicial);

      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(-250,-250,3);
        glTexCoord2f(1, 0); glVertex3f(250, -250 , 3);
        glTexCoord2f(1, 1); glVertex3f(250, 250, 3);
        glTexCoord2f(0, 1); glVertex3f(-250 , 250, 3);
      glEnd();
    glPopMatrix();
    }
      glDisable(GL_TEXTURE_2D);
     // glDisable(GL_DEPTH_TEST);
      glutSwapBuffers();
}
int main(int argc, char **argv){
    srand((unsigned)time(NULL));
    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Magic Journey Throught Nothing");
    inicializa();
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutTimerFunc(0, atualiza, 0);
    //glutSpecialFunc(handleSpecialKeypress);
    glutKeyboardUpFunc(handleSpecialKeyReleased);
    glutMainLoop();
    return 0;
}