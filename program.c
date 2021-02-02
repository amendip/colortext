#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFL 32768

unsigned int futf(unsigned char *str, unsigned int ui, unsigned int i){
unsigned int count=0;
while(str[i]!='\0'){
if(str[i]<128 || str[i]>=192){
count++;
if(count==ui+1) return i;
}
i++;
}
return i;
}

unsigned int utflen(unsigned char *str){
unsigned int i=0, count=0;
while(str[i]!='\0'){
if(str[i]<128 || str[i]>=192) count++;
i++;
}
return count;
}

void stripnl(char *str, size_t nr){
unsigned int i=0;
while(str[nr-1-i]=='\n' || str[nr-1-i]==' ' || str[nr-1-i]=='\t') str[nr-1-i]='\0', i++;
}

int main(int argc, char **argv) {
	char buf[BUFL];
	unsigned int color, tmp, n = 0, chars, charea, charearl, bufi=0, bufui=0, bufuichange=0, cmplr;
	unsigned char **colors; short **difference;
	float chardiff[3];

	if(argc > 2){
	n=argc-1;

	colors=(unsigned char**) malloc(n*sizeof(unsigned char*));
	for(int i=0; i<n; i++) colors[i]=(unsigned char*) malloc(3*sizeof(unsigned char));
	
	difference=(short**) malloc((n-1)*sizeof(short*));
	for(int i=0; i<n-1; i++) difference[i]=(short*) malloc(3*sizeof(short));

	}else{
	printf("please hex colors as arguments\n");
	return 1;
	}

	stripnl(buf, fread(buf, 1, BUFL, stdin));
	chars=utflen(buf);
	printf("you entered %d characters\n", chars);
	printf("you entered %d colors\n", n);

	for(int i=0;i<n;i++){
	sscanf(argv[i+1], "%6x", &color);

	colors[i][0]=color>>16;
	colors[i][1]=(color&0xff00)>>8;
	colors[i][2]=color&0xff;
	printf("RGB: %d, %d, %d\n", colors[i][0], colors[i][1], colors[i][2]); 

	if(i>0){
	difference[i-1][0]=colors[i][0]-colors[i-1][0];
	difference[i-1][1]=colors[i][1]-colors[i-1][1];
	difference[i-1][2]=colors[i][2]-colors[i-1][2];
	}
	}

	//generating
	for(int i=0;i<n-1;i++){
	charea=(chars-bufui)/(n-i-1);
	if((chars-bufui)%(n-1)!=0){
		if(i==n-2){
		charea=chars-bufui;
		}else{
		++charea;
		}
	}
	chardiff[0]=(float)difference[i][0]/(charea-(i==n-2));
	chardiff[1]=(float)difference[i][1]/(charea-(i==n-2));
	chardiff[2]=(float)difference[i][2]/(charea-(i==n-2));
	charearl=futf(buf, charea, bufi)-bufi;
	//printf("\nea%d earl%d bui%d bi%d\n", charea, charearl, bufi, bufui);
	//printf("%f %f %f\n", chardiff[0], chardiff[1], chardiff[2]);
	bufuichange=bufui;
	for(int j=0;j<charearl;j++){
		switch(buf[bufi+j]){
		case ' ': case '\n': case '\t': printf("%c", buf[bufi+j]); bufui++; break;
		default:
			if((unsigned char)buf[bufi+j]<128 || (unsigned char)buf[bufi+j]>=192){
			cmplr=bufui-bufuichange;
			printf("<font color=\"#%06x\">%c", 
				((colors[i][0]+(int)(chardiff[0]*cmplr))*0x10000 & 0xff0000)
				+((colors[i][1]+(int)(chardiff[1]*cmplr))*0x100 & 0xff00)
				+(colors[i][2]+(int)(chardiff[2]*cmplr) & 0xff), 
				buf[bufi+j]);
			if((unsigned char)buf[bufi+j]<128) printf("</font>");
			bufui++;
			}else if(j==charearl-1)
			printf("%c</font>", buf[bufi+j]);
			else if((unsigned char)buf[bufi+j+1]<128 || (unsigned char)buf[bufi+j+1]>=192)
			printf("%c</font>", buf[bufi+j]);
			else
			printf("%c", buf[bufi+j]);
		break;
		}
	}
	bufuichange=bufui-bufuichange;
	bufi=futf(buf, bufuichange, bufi);
	}
	printf("\n");
	for(int i=0; i<n; i++) free(colors[i]);
	free(colors); free(difference);
	return 0;
}
