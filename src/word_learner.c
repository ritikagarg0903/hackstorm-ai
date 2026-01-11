/**
 * @file word_learner.c
 * @brief word_learner module provides a rotating word list and helpers.
 * @version 0.1
 * @date 2025-04-30
 */

#include "word_learner.h"

#include "tal_api.h"

/***********************************************************
************************macro define************************
***********************************************************/
#define WORD_LEARNER_SEED_FALLBACK 0x6d3a2c19u

/***********************************************************
***********************typedef define***********************
***********************************************************/
typedef struct {
    const char *word;
    const char *meaning;
    const char *sample_sentence;
    const char *spelling;
} WORD_LEARNER_ENTRY_T;

/***********************************************************
***********************variable define**********************
***********************************************************/
static const WORD_LEARNER_ENTRY_T word_list[] = {
    {
        .word = "serendipity",
        .meaning = "The happy chance of finding something valuable or pleasant unexpectedly.",
        .sample_sentence = "Finding that book was pure serendipity during my walk.",
        .spelling = "s-e-r-e-n-d-i-p-i-t-y",
    },
    {
        .word = "resilient",
        .meaning = "Able to recover quickly from difficulties or adapt to change.",
        .sample_sentence = "The resilient plant thrived after the storm.",
        .spelling = "r-e-s-i-l-i-e-n-t",
    },
    {
        .word = "clarity",
        .meaning = "The quality of being easy to see, hear, read, or understand.",
        .sample_sentence = "Her explanation brought clarity to the plan.",
        .spelling = "c-l-a-r-i-t-y",
    },
    {
        .word = "curiosity",
        .meaning = "A strong desire to know or learn something.",
        .sample_sentence = "His curiosity led him to explore the new exhibit.",
        .spelling = "c-u-r-i-o-s-i-t-y",
    },
    {
        .word = "gratitude",
        .meaning = "A feeling of appreciation for kindness or benefits received.",
        .sample_sentence = "She expressed gratitude for the team’s support.",
        .spelling = "g-r-a-t-i-t-u-d-e",
    },
};

static uint32_t rng_state = 0;
static uint32_t current_word_index = 0;

/***********************************************************
***********************function define**********************
***********************************************************/
static uint32_t __word_learner_word_count(void)
{
    return (uint32_t)(sizeof(word_list) / sizeof(word_list[0]));
}

static void __word_learner_seed_if_needed(void)
{
    if (rng_state != 0) {
        return;
    }

    POSIX_TM_S tm = {0};
    tal_time_get_local_time_custom(0, &tm);

    rng_state = (uint32_t)((tm.tm_year + 1900) << 16)
                ^ (uint32_t)((tm.tm_mon + 1) << 12)
                ^ (uint32_t)(tm.tm_mday << 7)
                ^ (uint32_t)(tm.tm_hour << 2)
                ^ (uint32_t)(tm.tm_min << 1)
                ^ (uint32_t)(tm.tm_sec);

    if (rng_state == 0) {
        rng_state = WORD_LEARNER_SEED_FALLBACK;
    }
}

static uint32_t __word_learner_next_random(void)
{
    __word_learner_seed_if_needed();
    rng_state = (rng_state * 1103515245u) + 12345u;
    return rng_state;
}

void word_learner_pick_next(void)
{
    uint32_t word_count = __word_learner_word_count();

    if (word_count == 0) {
        current_word_index = 0;
        return;
    }

    current_word_index = __word_learner_next_random() % word_count;
}

const char *word_learner_get_current_word(void)
{
    return word_list[current_word_index].word;
}

const char *word_learner_get_meaning(void)
{
    return word_list[current_word_index].meaning;
}

const char *word_learner_get_sentence(void)
{
    return word_list[current_word_index].sample_sentence;
}

const char *word_learner_get_spelling(void)
{
    return word_list[current_word_index].spelling;
}
