#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int alphavit(int x) {
	return (('a' <= x) && (x <= 'z')) || (('A' <= x) && (x <= 'Z'));
}

int ponizhenie(int x) {
	if (('A' <= x) && x <= 'Z')
		return (x + 32);
	else
		return x;
}

int slovo1(char text[], char* begin[], char* end[])
{
	while (*text && !alphavit(*text)) {
		++text;
	}
	*begin = text;
	while (alphavit(*text)) {
		++text;
	}
	*end = text;
	return (*begin != *end);
}

char* sdvig(char text[], int len)
{
	for (; *text; *text = *(text + len), ++text) { ; }
	return text;
}

int Sravn(char first[], char second[], int len)
{
	for (; *first && *second && len && (ponizhenie(*first) == ponizhenie(*second)); ++first, ++second, --len) { ; }
	return (len == 0);
}

char* Copy2(char raz[], const char dva[], int len)
{
	for (; *dva && len; *raz++ = *dva++, --len) { ; }
	return raz;
}

char* PoiskDubl(char text[], char word[], int len)
{
	char* duplicate = NULL;
	char* begin;
	char* end;
	for (; !duplicate && slovo1(text, &begin, &end); text = end + 1)
	{
		if (((end - begin) == len) && Sravn(begin, word, len))
		{
			duplicate = begin;
		}
	}
	return duplicate;
}

char DeleteDubl(char text[], char result[])
{
	int count = 0;
	char* begin;
	char* end;
	char* cursor;
	int find;
	for (; slovo1(text, &begin, &end); text = end + 1)
	{
		for (cursor = end + 1, find = 0; (cursor = PoiskDubl(cursor, begin, end - begin)) != NULL; ++find)
		{
			sdvig(cursor, end - begin);
		}
		if (find)
		{
			result = Copy2(result, begin, end - begin);
			*result++ = ' ';
			sdvig(begin, end - begin);
			end = begin;
		}
	}
	return count;
}

int main()
{
	int count;
	printf("input text: ");
	char text[100];
	fgets(text, 100, stdin);
	char result[100] = { 0 };
	count = DeleteDubl(text, result);
	printf("Result:\n");
	printf("%s", result);
	return 0;
}
