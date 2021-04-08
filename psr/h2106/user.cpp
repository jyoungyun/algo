#include <stdio.h>
#include <assert.h>

#define MAX_N			5
#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

#define MAX_BOOKS		50000
#define MAX_M			(100 + 1)
#define MAX_TYPES		500

#define assertStr(condition, format, ...) \
do { \
	if ( ! (condition) ) { \
		fprintf(stderr, format, ## __VA_ARGS__); \
		assert(condition); \
	} \
} while(false)

// #define DEBUG

#ifdef DEBUG
#define myprintf printf
#else
#define myprintf 
#endif

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

typedef struct {
	char name[MAX_NAME_LEN];
	int typeLen;
	char types[MAX_N][MAX_TAG_LEN];
	int section;
	char checked;
} Book;
Book books[MAX_BOOKS];
int books_length;

typedef struct {
	char key[MAX_NAME_LEN];
	Book* data;
} BookHashTable;
BookHashTable bookHash[MAX_BOOKS];

struct BookNode {
	Book* data;
	BookNode *next;
};
struct BookNode types[MAX_BOOKS * MAX_N];
int types_length;

typedef struct {
	char key[MAX_TAG_LEN];
	BookNode* list;
} TypeHashTable;

typedef struct {
	TypeHashTable typeHash[MAX_TYPES];
} Library;
Library library[MAX_M];
int library_length;

unsigned long nameHash(const char* key) {
	int sum = 0;
	for (int i = 0; key[i] != '\0'; ++i) {
		sum += key[i];
	}
	return sum % MAX_BOOKS;
}

int addBookHashTable(const char* key, Book* data) {
	unsigned long h = nameHash(key);
	while (bookHash[h].key[0] != 0) {
		assertStr(mstrcmp(bookHash[h].key, key) != 0, "Add %s book that is already inserted.\n");
		h = (h + 1) % MAX_BOOKS;
	}
	mstrcpy(bookHash[h].key, key);
	bookHash[h].data = data;
	return 0;
}

Book* findBookHashTable(const char *key) {
	unsigned long h = nameHash(key);
	int cnt = MAX_BOOKS;

	if (mstrcmp(key, "PaXw") == 0) {
		myprintf("Searching PaXw...");
	}
	while (bookHash[h].key[0] != 0 && cnt--) {
		if (mstrcmp(bookHash[h].key, key) == 0) {
			if (mstrcmp(key, "PaXw") == 0) {
				myprintf("return %s\n", bookHash[h].data->name);
			}
			return bookHash[h].data;
		}
		h = (h + 1) % MAX_BOOKS;
	}
				if (mstrcmp(key, "PaXw") == 0) {
				myprintf("null???");
			}
	return nullptr;
}

Book* deleteBookHashTable(const char *key) {
	unsigned long h = nameHash(key);
	while (bookHash[h].key[0] != 0) {
		if (mstrcmp(bookHash[h].key, key) == 0) {
			Book *book = bookHash[h].data;
			bookHash[h].data = nullptr;
			return book;
		}
		h = (h + 1) % MAX_BOOKS;
	}
	return nullptr;
}

int typeHash(const char* key) {
	int sum = 0;
	for (int i = 0; key[i] != '\0'; ++i) {
		sum += key[i];
	}
	return sum % MAX_TYPES;
}

int addTypeHashTable(int mSection, const char *key, BookNode *node) {
	unsigned long h = typeHash(key);
	while (library[mSection].typeHash[h].key[0] != 0) {
		if (mstrcmp(library[mSection].typeHash[h].key, key) == 0) {
			break;
		}
		h = (h + 1) % MAX_TYPES;
	}
	if (library[mSection].typeHash[h].key[0] == 0) {
		mstrcpy(library[mSection].typeHash[h].key, key);
	}
	if (library[mSection].typeHash[h].list == nullptr) {
		library[mSection].typeHash[h].list = node;
	} else {
		BookNode *prev = nullptr;
		for (BookNode *p = node; p != nullptr; prev = p, p = p->next) {
			;
		}
		if (prev == nullptr) {
			node->next = library[mSection].typeHash[h].list;
		} else {
			prev->next = library[mSection].typeHash[h].list;
		}
		library[mSection].typeHash[h].list = node;
	}
}

BookNode *findTypeHashTable(int mSection, const char *key) {
	unsigned long h = typeHash(key);
	while (library[mSection].typeHash[h].key[0] != 0) {
		if (mstrcmp(library[mSection].typeHash[h].key, key) == 0) {
			return library[mSection].typeHash[h].list;
		}
		h = (h + 1) % MAX_TYPES;
	}
	return nullptr;
}

BookNode* deleteTypeHashTable(int mSection, const char *key) {
	unsigned long h = typeHash(key);

	while (library[mSection].typeHash[h].key[0] != 0) {
		if (mstrcmp(library[mSection].typeHash[h].key, key) == 0) {
			BookNode *list = library[mSection].typeHash[h].list;
			// library[mSection].typeHash[h].key[0] = 0;
			library[mSection].typeHash[h].list = nullptr;
			return list;
		}
		h = (h + 1) % MAX_TYPES;
	}
	return nullptr;
}

BookNode* deleteBookTypeHashTable(int mSection, const char *key, const char *name) {
	unsigned long h = typeHash(key);

	while (library[mSection].typeHash[h].key[0] != 0) {
		if (mstrcmp(library[mSection].typeHash[h].key, key) == 0) {
			for (BookNode *p = library[mSection].typeHash[h].list, *prev = nullptr; p != nullptr; prev = p, p = p->next) {
				if (mstrcmp(p->data->name, name) == 0) {
					BookNode *list = p;
					if (prev == nullptr) {
						library[mSection].typeHash[h].list = p->next;
					} else {
						prev->next = p->next;
					}
					// if (library[mSection].typeHash[h].list == nullptr) {
					// 	library[mSection].typeHash[h].key[0] = 0;
					// }
					list->next = nullptr;
					return list;
				}
			}
		}
		h = (h + 1) % MAX_TYPES;
	}
	return nullptr;
}

void debugAllBookPrint() {
	for (int i = 0; i < books_length; ++i) {
		Book *book = &books[i];
		myprintf("[BOOK] %s, (", book->name);
		for (int i = 0; i < book->typeLen; ++i) {
			myprintf("%s ", book->types[i]);
		}
		myprintf(") Section: %3d\n", book->section);
	}
}

void debugBookPrint(const char *key) {
	Book *book = findBookHashTable(key);
	if (book != nullptr) {
		myprintf("[BOOK] %s, (", book->name);
		for (int i = 0; i < book->typeLen; ++i) {
			myprintf("%s ", book->types[i]);
		}
		myprintf(") Section: %3d\n", book->section);
	}
}

void debugPrint(void) {
	for (int i = 0; i < library_length; ++i) {
		myprintf("[%3d Section]\n", i);
		for (int j = 0; j < MAX_TYPES; ++j) {
			if (library[i].typeHash[j].key[0] != 0) {
				myprintf("\t(%3d Type[%s])\n\t\t", j, library[i].typeHash[j].key);
				for (BookNode *p = library[i].typeHash[j].list; p != nullptr; p = p->next) {
					myprintf("%s -> ", p->data->name);
				}
				myprintf("\n");
			}
		}
	}
}

void init(int M)
{
	// reset books and bookHashtable
	books_length = 0;
	types_length = 0;
	for (int i = 0; i < MAX_BOOKS; ++i) {
		books[i].typeLen = 0;
		bookHash[i].key[0] = 0;
	}
	library_length = M + 1;
	for (int i = 0; i < library_length; ++i) {
		for (int j = 0; j < MAX_TYPES; ++j) {
			library[i].typeHash[j].key[0] = 0;
			library[i].typeHash[j].list = nullptr;
		}
	}
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	myprintf("%s %d %d\n", mName, mTypeNum, mSection);
	Book *book = &books[books_length++];
	mstrcpy(book->name, mName);
	book->typeLen = mTypeNum;
	book->checked = 0;
	for (int i = 0; i < mTypeNum; ++i) {
		mstrcpy(book->types[i], mTypes[i]);
	}
	book->section = mSection;

	addBookHashTable(mName, book);
	for (int i = 0; i < mTypeNum; ++i) {
		BookNode* bookNode = &types[types_length++];
		bookNode->data = book;
		bookNode->next = nullptr;
		addTypeHashTable(mSection, mTypes[i], bookNode);
	}

	debugPrint();
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
	BookNode *fromList = deleteTypeHashTable(mFrom, mType);
	if (fromList == nullptr) {
		myprintf("Must not happen this case, No list");
		return 1;
	}

	int count = 0;
	for (BookNode *p = fromList; p != nullptr; p = p->next) {
		for (int i = 0; i < p->data->typeLen; ++i) {
			if (mstrcmp(p->data->types[i], mType) == 0) {
				continue;
			}
			BookNode *node = deleteBookTypeHashTable(mFrom, p->data->types[i], p->data->name);
			assertStr(node != nullptr, "moveType: %s %d -> %d\n", mType, mFrom, mTo);
			addTypeHashTable(mTo, p->data->types[i], node);
		}
		p->data->section = mTo;
		count++;
	}

	addTypeHashTable(mTo, mType, fromList);

	debugPrint();
	return count;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
	debugBookPrint(mName);
	Book* book = findBookHashTable(mName);
	if (book == nullptr) {
		myprintf("Must not happen this case, No book\n");
		return;
	}

	for (int i = 0; i < book->typeLen; ++i) {
		BookNode *node = deleteBookTypeHashTable(book->section, book->types[i], mName);
		assertStr(node != nullptr, "moveName: %s %s type to %d from %d\n", mName, book->types[i], mSection, book->section);
		addTypeHashTable(mSection, book->types[i], node);
	}

	book->section = mSection;

	debugPrint();
}

void deleteName(char mName[MAX_NAME_LEN])
{
	if (mstrcmp(mName, "PaXw") == 0) {
		debugAllBookPrint();
	}
	debugBookPrint(mName);
	Book* book = deleteBookHashTable(mName);

	for (int i = 0; i < book->typeLen; ++i) {
		deleteBookTypeHashTable(book->section, book->types[i], mName);
	}

	debugPrint();
}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	debugPrint();
	int total = 0;
	for (int i = 0; i < mTypeNum; ++i) {
		myprintf("type: %s\n", mTypes[i]);
		BookNode *node = findTypeHashTable(mSection, mTypes[i]);
		myprintf("node: %p\n", node);
		for (BookNode *p = node; p != nullptr; p = p->next) {
			myprintf("book: %s(%c)\n", p->data->name, p->data->checked);
			if (p->data->checked == 0) {
				total++;
				p->data->checked = 1;
			}
		}
	}

	for (int i = 0; i < mTypeNum; ++i) {
		BookNode *node = findTypeHashTable(mSection, mTypes[i]);
		for (BookNode *p = node; p != nullptr; p = p->next) {
			myprintf("book: %s(%c)\n", p->data->name, p->data->checked);
			if (p->data->checked == 1) {
				myprintf("removed!\n");
				p->data->checked = 0;
			}
		}
	}

	return total;
}