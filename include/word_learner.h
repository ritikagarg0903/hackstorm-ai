/**
 * @file word_learner.h
 * @brief word_learner module provides a rotating word list and helpers.
 * @version 0.1
 * @date 2025-04-30
 */

#ifndef __WORD_LEARNER_H__
#define __WORD_LEARNER_H__

#include "app_display.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************macro define************************
***********************************************************/

/***********************************************************
********************function declaration********************
***********************************************************/

/**
 * @brief Picks the next word from the list.
 */
void word_learner_pick_next(void);

/**
 * @brief Picks the next word and returns it.
 */
const char *word_learner_next_word(void);

/**
 * @brief Gets the current word text.
 */
const char *word_learner_get_current_word(void);

/**
 * @brief Gets the current word text (alias for current word).
 */
const char *word_learner_current_word(void);

/**
 * @brief Gets the meaning of the current word.
 */
const char *word_learner_get_meaning(void);

/**
 * @brief Gets the sample sentence for the current word.
 */
const char *word_learner_get_sentence(void);

/**
 * @brief Gets the spelling for the current word.
 */
const char *word_learner_get_spelling(void);

/**
 * @brief Fill a display payload with the current word details.
 */
void word_learner_fill_display(WORD_LEARNER_DISPLAY_T *card);

#ifdef __cplusplus
}
#endif

#endif /* __WORD_LEARNER_H__ */
