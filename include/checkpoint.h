#pragma once

void save_checkpoint(const char* filename, int episode);
int load_checkpoint(const char* filename, int *episode);