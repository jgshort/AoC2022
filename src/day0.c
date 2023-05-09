#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "../include/day0.h"
#include "../include/utils.h"

/*
--- Day 1: Calorie Counting ---

The Elves take turns writing down the number of Calories contained by the
various meals, snacks, rations, etc. that they've brought with them, one item
per line. Each Elf separates their own inventory from the previous Elf's
inventory (if any) by a blank line.

For example, suppose the Elves finish writing their items' Calories and end up
with the following list:

1000
2000
3000

4000

5000
6000

7000
8000
9000

10000

This list represents the Calories of the food carried by five Elves:

    The first Elf is carrying food with 1000, 2000, and 3000 Calories, a total of 6000 Calories.
    The second Elf is carrying one food item with 4000 Calories.
    The third Elf is carrying food with 5000 and 6000 Calories, a total of 11000 Calories.
    The fourth Elf is carrying food with 7000, 8000, and 9000 Calories, a total of 24000 Calories.
    The fifth Elf is carrying one food item with 10000 Calories.

In case the Elves get hungry and need extra snacks, they need to know which Elf
to ask: they'd like to know how many Calories are being carried by the Elf
carrying the most Calories. In the example above, this is 24000 (carried by the
fourth Elf).

Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?
*/

int aoc_day0_p0(int argc, char **argv) {
  if(argc < 4) { goto err0; }

  const char * input = argv[3];

  FILE * fp = fopen(input, "r");
  if(!fp || errno) { goto err1; }

  char * line = NULL;
  size_t len = 0;
  ssize_t read = 0;

  size_t current_elf = 0, best_elf = 0;
  unsigned long total_calories = 0, max_calories = 0;
  while((read = getline(&line, &len, fp)) != -1) {
    if(errno) { goto err2; }
    if(read <= 1) {
      if(total_calories > max_calories) {
        best_elf = current_elf;
        max_calories = total_calories;
      }
      total_calories = 0;
      current_elf++;
      continue;
    }

    unsigned long item_calories = parse_arg(line, false);
    total_calories += item_calories;
  }
  fclose(fp);
  free(line), line = NULL;

  fprintf(stdout, "best elf: %zu, max calories: %zu\n", best_elf + 1, max_calories);

  return EXIT_SUCCESS;

err2:
  fclose(fp);
  free(line), line = NULL;
  fprintf(stderr, "oh no, i can't read a line from '%s'! i'm dead. :(\n", input);
  goto err;

err1:
  fprintf(stderr, "'%s' doesn't exist or i couldn't open it. i tried :(\n", input);
  goto err;

err0:
  fprintf(stderr, "listen, i need a path/file name, bud.\n");
  fprintf(stderr, "usage: aoc 0 0 <path>\n");
  goto err;

err:
  return EXIT_FAILURE;
}

