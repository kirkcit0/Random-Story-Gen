//Kirk Lefevre
//Dr. Steinberg
//COP3502C Spring 2022
//Programming Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 20

char ** doubleIt(char **arr, int *maxsize);
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize);
char* generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize); //write sentence to console window
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr); //write story to txt file
void displaySentence(char * sentence);
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize);

int main()
{
	//setup randomness
	int x;
	printf("Enter seed: ");
	scanf("%d", &x);
	srand(x); //set seed
	
	//declare necessary variables
	int nounsize = 0;
	int verbsize = 0;
	int adjsize = 0;
	int prepositionsize = 0;
	
	int nounmaxsize = 5;
	int verbmaxsize = 5;
	int adjmaxsize = 5;
	int prepositionmaxsize = 5;
	const int articlemaxsize = 3; //there are only 3 articles in the english language a, an, and the. that is why const is applied
	
	printf("Welcome to the random sentence generator.\n");
	
	//double pointers
	char ** nouns = NULL;
	char ** verbs = NULL;
	char ** adjectives = NULL;
	char ** preposition = NULL;
	char ** articles = NULL;
	
	nouns = (char **) malloc(sizeof(char *) * nounmaxsize); 
	verbs = (char **) malloc(sizeof(char *) * verbmaxsize);
	adjectives = (char **) malloc(sizeof(char *) * adjmaxsize); 
	preposition = (char **) malloc(sizeof(char *) * prepositionmaxsize); 
	articles = (char **) malloc(sizeof(char *) * articlemaxsize); 
	
	//make sure malloc was able to allocate memory
	if(nouns == NULL || verbs == NULL || adjectives == NULL || preposition == NULL || articles == NULL) 
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}
	
	//populate articles using strcat. numbers represent how many characters are needed. this includes \0 character
	articles[0] = (char *) malloc(sizeof(char) * 2);
	strcat(articles[0], "A");
	articles[1] = (char *) malloc(sizeof(char) * 3);
	strcat(articles[1], "An");
	articles[2] = (char *) malloc(sizeof(char) * 4);
	strcat(articles[2], "The");
	
	//open the file of words
	FILE *fptr = fopen("nouns.txt", "r");
	FILE *fptr2 = fopen("verbs.txt", "r");
	FILE *fptr3 = fopen("adjectives.txt", "r");
	FILE *fptr4 = fopen("preposition.txt", "r");
	
	//make sure the files were opened properly
	if(fptr == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL)
	{
		printf("file was not successful in opening.");
		printf("Program will now terminate.\n");
		exit(1);
	}
	
	//populate the dynamic array
	nouns = populate(nouns, fptr, &nounsize, &nounmaxsize); //populate nouns
	verbs = populate(verbs, fptr2, &verbsize, &verbmaxsize); //populate verbs
	adjectives = populate(adjectives, fptr3, &adjsize, &adjmaxsize); //populate adjectives
	preposition = populate(preposition, fptr4, &prepositionsize, &prepositionmaxsize); //populate prepositions
	
	//close the files
	fclose(fptr);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);

	//now lets generate 5 sentences and write them to the console window

	printf("Let's generate some random sentences that don't make sense.\n");

	for(int x = 0; x < 5; ++x)
	{
		char * sentence = generateSentence(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize);
		displaySentence(sentence);
		free(sentence);
	}
	
	printf("Now let's create three stories that just don't make sense.\n");
	fptr = fopen("story1.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 1
	fclose(fptr);
	
	fptr = fopen("story2.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 2
	fclose(fptr);

	fptr = fopen("story3.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 3
	fclose(fptr);

	cleanUp(nouns,verbs, adjectives, preposition, articles, nounmaxsize, verbmaxsize, adjmaxsize, prepositionmaxsize, 3);

	
	printf("The stories were generated successfully and stored in their respective text files.\n");
	printf("Check them out!\n");
	
	return 0;
}

//populate each word type
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize){
	int i, k=0;
	int size=0;
	int c;

	//count number of lines in the file for currentsize, increase maxsize
	for(c = fgetc(fptr); c != EOF; c = fgetc(fptr)){
		if(c=='\n')
			k++;
		if(k==*maxsize)
			doubleIt(words, maxsize);
	}
	//currentsize++ wasnt working out so use primitive variable and set currentsize=k;
	k++;
	*currentsize=k;

	//go back to beginning of file
	fseek(fptr, 0, SEEK_SET);
	
	//free then allocate new memory to words array
	free(words);
	words=(char**) malloc(sizeof(char*)**maxsize);
	if(words==NULL){
		printf("failure in populate");
		exit(1);
	}

	//allocate for each string and fill with the words
	for(i=0; i<*currentsize;i++){
		words[i]=(char*) malloc(sizeof(char)*LIMIT);
		if(words[i]==NULL){
			printf("dang it failed to allocate in populate");
			exit(1);
		}
		fscanf(fptr, "%s", words[i]);
		if(feof(fptr))
			break;	
	}

	/*
	for(i=0; i<*currentsize; i++){
		printf("%s\n", words[i]);
	}
	printf("\n\n");
	*/
	

	return words;
}

//increase allocated memory for each array
char ** doubleIt(char **arr, int *maxsize){

	//double the maxsize :)
	*maxsize=*maxsize*2;

	return 0;
}

//generate sentences
char* generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize){
	
	//declare sentence array
	char *sentence;

	//allocate space for sentence array for 100 characters maximum
	sentence=(char*) malloc(sizeof(char)*100);
	if(sentence==NULL){
		printf("failure in generatesentece");
		exit(1);
	}

	//form the sentence
	strcpy(sentence, article[rand()%articlesize]);
	strcat(sentence, " ");
	strcat(sentence, adjective[rand()%adjsize]);
	strcat(sentence, " ");
	strcat(sentence, noun[rand()%nounsize]);
	strcat(sentence, " ");
	strcat(sentence, verb[rand()%verbsize]);
	strcat(sentence, " ");
	strcat(sentence, preposition[rand()%prepositionsize]);
	strcat(sentence, " ");
	strcat(sentence, article[rand()%articlesize]);
	strcat(sentence, " ");
	strcat(sentence, adjective[rand()%adjsize]);
	strcat(sentence, " ");
	strcat(sentence, noun[rand()%nounsize]);
	strcat(sentence, ".\n");
	

	return sentence;
}

//display sentence
void displaySentence(char * sentence){
	
	//print sentence to terminal
	printf("%s", sentence);
}

//generate the stories in text files
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr){

	//declare sentence array
	char *sentence;

	//set random number between 100 and 500
	int rannum = (rand()%401)+100;

	//make 100-500 sentence with generate sentence
	for(int i=0; i<rannum; i++){

		sentence=generateSentence(noun, verb, adjective, preposition, article, nounsize, verbsize, adjsize, prepositionsize, articlesize);

		//print sentences to file, free sentence array
		fprintf(fptr, "%s", sentence);
		free(sentence);
	}
}

//clean up all those arrays
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize){

	int i;

	//free all strings
	for(i=0; i<nounsize; i++){
		free(nouns[i]);
	}
	for(i=0; i<verbsize; i++){
		free(verbs[i]);
	}
	for(i=0;i<adjsize;i++){
		free(adjectives[i]);
	}
	for(i=0;i<prepositionsize;i++){
		free(prepositions[i]);
	}
	for(i=0;i<articlesize;i++){
		free(articles[i]);
	}

	//free all arrays
	free(nouns);
	free(verbs);
	free(adjectives);
	free(prepositions);
	free(articles);


}







//the end :)