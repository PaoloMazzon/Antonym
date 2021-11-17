/// \file Save.c
/// \author Paolo Mazzon
#include "Nym/Save.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"

// Creates a default save file
void _nymSaveCreateDefault(NymSave save) {
	save->saveVersion = NYM_SAVE_VERSION;
	save->rendererConfig.filterMode = ft_Nearest;
	save->rendererConfig.screenMode = sm_TripleBuffer;
	save->rendererConfig.msaa = msaa_32x;
	strcpy(save->lastIP, "127.0.0.1");
	strcpy(save->lastPort, "7000");
	strcpy(save->lastName, "JOE MAMA");
}

// Loads a save from a buffer assuming the save version is already set
void _nymSaveLoad(JUBuffer buffer, NymSave save) {
	if (save->saveVersion == NYM_SAVE_VERSION && buffer->size == sizeof(struct NymSave)) {
		// Latest save version - just copy buffer over
		memcpy(save, buffer->data, buffer->size);
	} else {
		// Corrupt/incompatible save version
		nymLog(NYM_LOG_LEVEL_ERROR, "Save file is corrupt, creating new default save.");
		_nymSaveCreateDefault(save);
	}
}

NymSave nymSaveLoad(const char *file) {
	JUBuffer buffer = juBufferLoad(file);
	NymSave save = nymCalloc(sizeof(struct NymSave));

	if (buffer != NULL && buffer->size >= 4) {
		// Copy the save version
		memcpy(save, buffer->data, sizeof(uint32_t));

		// Load the save based on the version
		_nymSaveLoad(buffer, save);
	} else {
		nymLog(NYM_LOG_LEVEL_WARNING, "No compatible save file located. Creating new save.");
		_nymSaveCreateDefault(save);
	}

	juBufferFree(buffer);

	return save;
}

void nymSaveFlush(NymSave save, const char *file) {
	juBufferSaveRaw(save, sizeof(struct NymSave), file);
}

void nymSaveDestroy(NymSave save) {
	nymFree(save);
}