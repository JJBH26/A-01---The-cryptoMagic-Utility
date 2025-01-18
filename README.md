# A-01---The-cryptoMagic-Utility

The `cryptoMagic` utility is a simple file encryption and decryption program written in C. It allows you to encrypt or decrypt text files by performing character-based transformations, making it an introductory project for understanding file I/O, encryption, and decryption techniques.

## Features

- Encrypt and decrypt files with a simple command-line interface.
- Encrypt characters by shifting their ASCII values and converting them to a hexadecimal format.
- Decrypt files by reversing the encryption process and restoring the original content.

## How to Use

### Encryption

To encrypt a file, use the `--encrypt` option followed by the name of the file you want to encrypt.

`cryptoMagic --encrypt <inputFileName>`
This will generate an encrypted file with the .crp extension.

Decryption
To decrypt an encrypted file, use the `--decrypt` option followed by the name of the file to decrypt.

Edit
`cryptoMagic --decrypt <inputFileName>`
This will generate a decrypted file with the .txt extension.

Example Usage

`cryptoMagic --encrypt myFile.txt`
`cryptoMagic --decrypt myFile.crp`
