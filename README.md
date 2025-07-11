# tokiponavocab

Train Toki Pona words, or any other language.

## How it works

See repetition.md, and repetition.c for more detail on how the repetition algorithm works.

By default, 5 words are selected. Once a word is correct 5 times in a row, it is replaced with a new one. Periondically, a previously learned card is brought back for review.

## Config

config.h lets you tweak how the repetition algorith works, as well as things like the default language and where the languages are stored.

## Building and running

```
make
./trainer # Will train DEFAULT_LANGUAGE
./trainer language_name # Will train language_name.json
```

### Requirnments

```
https://github.com/json-c/json-c
```
