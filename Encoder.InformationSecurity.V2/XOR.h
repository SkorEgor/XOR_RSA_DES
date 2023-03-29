CString XOR(CString input_text, CString input_key) {
	CString Ciphertext;
	for (int i = 0; i < input_text.GetLength(); i++) {
		Ciphertext.AppendChar(input_text[i] ^ input_key[i % 4]);
	}
	return(Ciphertext);
}