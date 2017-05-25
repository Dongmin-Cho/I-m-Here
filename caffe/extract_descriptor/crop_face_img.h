/*
	*	@brief					facial frontalization with non reflection similarity transform \n
	*	@param [in]				inIm				input image \n
	*	@param [in]				EyelocL				Left Eye Position, opencv structure \n
	*	@param [in]				EyelocR				Right Eye Position, opencv structure \n
	*	@param [in]				cropWidth			Width to be cropped image \n
	*	@param [in]				cropHeight			Height to be cropped image  \n
	*	@param [in]				eye_hLevel			eye height position (pixel) in the cropped image (ex. n: ¾ó±¼ÀÇ 1/n À§Ä¡¿¡ ´« À§Ä¡, dafault = 3) \n
	*	@return					Cropped and frontalized \n
	*/
Mat _cropFaceImagebyEYE(Mat inIm, Point2f EyelocL, Point2f EyelocR, int cropWidth, int cropHeight, float feyewidRatio = 0.4f, float feyehLevel = 0.38f);