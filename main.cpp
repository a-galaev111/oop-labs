#include "csv_writer.h"
#include "text_reader.h"
#include "word_counter.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    TextReader reader;
    reader.readFile(argv[1]);

    WordCounter counter;
    counter.countWords(reader.getText());

    CsvWriter writer;
    writer.writeCsv(argv[2], counter.getWordsCounter(), counter.getTotalWords());

    return 0;
}
