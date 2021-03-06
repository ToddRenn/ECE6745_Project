This final project for ECE6745 aims to demonstrate algebraic attacks
on a 32 bit block cipher circuit through Grobner Basis techniques.

# FILE DESCRIPTION
> **converter.cpp** This file converts ASCII input to polynomial representation.
> **block_cipher.lib** This file contains functions that convert plaintext to ciphertext.
> **Full_Block_Cipher.sing** This file generates the Grobner basis for the given block cipher with an input of plaintext and a key. 

# STEPS TO RUN
> ## STEP1: Compile converter.cpp using the following command:
>> *g++ converter.cpp -o convert*

> ## STEP2: In **Full_Block_Cipher.sing**
>> 2a. Set the cipher text on line 56, position 46. (Limit 4 characters)
>> 2b. Set the key on line 63, position 38. (Limit 4 characters)

> ## STEP3: Execute **Full_Block_Cipher.sing** in Singular

# KEY RECOVERY
> ## STEP1. In Singular, execute the command:
>>	G; // Look for elements containing key bits (k_[0:3]) and take note
> ## STEP2. In Singular, execute the command: 
>>	fact_list(G); // Returns factored univariate members of the GB
> ## STEP3. Evaluate key polynomials
> ## STEP4. Test recovered key solution to see if you get the same ciphertext given the same plaintext input.
