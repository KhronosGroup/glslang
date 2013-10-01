#version 330 core

// cross-unit recursion

void main() {}

// two-level recursion

float cbar(int);

void cfoo(float)
{
	cbar(2);
}

// four-level, out of order

void CB();
void CD();
void CA() { CB(); }
void CC() { CD(); }

// high degree

void CBT();
void CDT();
void CAT() { CBT(); CBT(); CBT(); }
void CCT() { CDT(); CDT(); CBT(); }
