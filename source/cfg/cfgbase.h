/*
 * cfgbase.h
 *
 *  Created on: 07.09.2018
 *      Author: bsa
 */

#include <stdint.h>

#ifndef CFGBASE_H_
#define CFGBASE_H_

#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */

namespace nsCFG
{
    const uint32_t _BUFF_MAX = 256; // max length parameter name
};

#endif /* CFGBASE_H_ */
