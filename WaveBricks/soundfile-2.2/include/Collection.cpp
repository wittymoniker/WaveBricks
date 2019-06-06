//
// Copyright 1997 by Craig Stuart Sapp, All Rights Reserved.
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Feb  5 19:42:53 PST 1997
// Last Modified: Wed Apr 23 22:08:34 GMT-0800 1997
// Last Modified: Fri Sep 14 15:50:52 PDT 2001 (added last() function)
// Last Modified: Wed Mar 30 14:00:16 PST 2005 (Fixed for compiling in GCC 3.4)
// Filename:      ...sig/maint/code/base/Collection/Collection.cpp
// Web Address:   http://sig.sapp.org/src/sigBase/Collection.cpp
// Syntax:        C++ 
//
// Description:   A dynamic array which can grow as necessary.
//                This class can hold any type of item, but the
//                derived Array class is specifically for collections
//                of numbers.
//

#ifndef _COLLECTION_CPP_INCLUDED
#define _COLLECTION_CPP_INCLUDED

#include "Collection.h"
#include <iostream>
#include <stdlib.h>


//////////////////////////////
//
// Collection::Collection 
//

template<class type>
Collection<type>::Collection(void) {
   this->allocSize = 0;
   this->size = 0;
   this->array = NULL;
   this->allowGrowthQ = 0;
   this->growthAmount = 8;
   this->maxSize = 0;
}

template<class type>
Collection<type>::Collection(int arraySize) {
   this->array = new type[arraySize];
   this->size = arraySize;
   this->allocSize = arraySize;
   this->allowGrowthQ = 0;
   this->growthAmount = arraySize;
   this->maxSize = 0;
}


template<class type>
Collection<type>::Collection(int arraySize, type *aCollection) {
   this->size = arraySize;
   this->allocSize = arraySize;
   this->array = new type[size];
   for (int i=0; i<size; i++) {
      this->array[i] = aCollection[i];
   }
   this->growthAmount = arraySize;
   this->allowGrowthQ = 0;
   this->maxSize = 0;
}


template<class type>
Collection<type>::Collection(Collection<type>& aCollection) {
   this->size = aCollection.size;
   this->allocSize = size;
   this->array = new type[size];
   for (int i=0; i<size; i++) {
      this->array[i] = aCollection.array[i];
   }
   this->allowGrowthQ = aCollection.allowGrowthQ;
   this->growthAmount = aCollection.growthAmount;
   this->maxSize = aCollection.maxSize;
}



//////////////////////////////
//
// Collection::~Collection
//

template<class type>
Collection<type>::~Collection() {
   if (this->getAllocSize() != 0) {
      delete [] this->array;
   }
}



//////////////////////////////
//
// Collection::allowGrowth
//	default value: status = 1 
//

template<class type>
void Collection<type>::allowGrowth(int status) {
   if (status == 0) {
      this->allowGrowthQ = 0;
   } else {
      this->allowGrowthQ = 1;
   }
}



//////////////////////////////
//
// Collection::append 
//

template<class type>
void Collection<type>::append(type& element) {
   if (this->size == this->getAllocSize()) {
      this->grow();
   }
   this->array[size] = element;
   this->size++;
}

template<class type>
void Collection<type>::appendcopy(type element) {
   if (this->size == this->getAllocSize()) {
      this->grow();
   }
   this->array[size] = element;
   this->size++;
}

template<class type>
void Collection<type>::append(type *element) {
   if (this->size == this->getAllocSize()) {
      this->grow();
   }
   this->array[size] = *element;
   this->size++;
}



//////////////////////////////
//
// Collection::grow 
// 	default parameter: growamt = -1
//

template<class type>
void Collection<type>::grow(long growamt) {
   this->allocSize += growamt > 0 ? growamt : this->growthAmount;
   if (this->maxSize != 0 && this->getAllocSize() > this->maxSize) {
      std::cerr << "Error: Maximum size allowed for array exceeded." << std::endl;
      exit(1);
   }
 
   type *temp = new type[this->getAllocSize()];
   for (int i=0; i<size; i++) {
      temp[i] = this->array[i];
   }
   this->array = temp;
}



//////////////////////////////
//
// Collection::pointer
//

template<class type>
type* Collection<type>::pointer(void) {
   return this->array;
}



//////////////////////////////
//
// Collection::getBase
//

template<class type>
type* Collection<type>::getBase(void) {
   return this->array;
}



//////////////////////////////
//
// Collection::getAllocSize
//

template<class type>
long Collection<type>::getAllocSize(void) const {
   return this->allocSize;
}



//////////////////////////////
//
// Collection::getSize --
//

template<class type>
long Collection<type>::getSize(void) const {
   return this->size;
}



//////////////////////////////
//
// Collection::last --
//

template<class type>
type& Collection<type>::last(void) {
   return this->array[getSize()-1];
}



//////////////////////////////
//
// Collection::setAllocSize
//

template<class type>
void Collection<type>::setAllocSize(long aSize) {
   if (aSize < this->getSize()) {
      std::cerr << "Error: cannot set allocated size smaller than actual size." 
           << std::endl;
      exit(1);
   }

   if (aSize <= this->getAllocSize()) {
      this->shrinkTo(aSize);
   } else {
      this->grow(aSize-this->getAllocSize());
      this->size = aSize;
   }
}



//////////////////////////////
//
// Collection::setGrowth
//	default parameter: growth = -1
//

template<class type>
void Collection<type>::setGrowth(long growth) {
   if (growth > 0) {
      this->growthAmount = growth;
   }
}



//////////////////////////////
//
// Collection::setSize
//

template<class type>
void Collection<type>::setSize(long newSize) {
   if (newSize <= this->getAllocSize()) { 
      this->size = newSize;
   } else {
      this->grow(newSize-this->getAllocSize());
      this->size = newSize;
   }
}



////////////////////////////////////////////////////////////////////////////////
//
// Collection operators
//

//////////////////////////////
//
// Collection::operator[]
//

template<class type>
type& Collection<type>::operator[](int elementIndex) {
   if (this->allowGrowthQ && elementIndex == this->size) {
      if (this->size == this->getAllocSize()) {
         this->grow();
      }
      this->size++;
   } else if (elementIndex >= this->size) {
      std::cerr << "Error: accessing invalid array location " 
           << elementIndex 
           << " Maximum is " << this->size-1 << std::endl;
      exit(1);
   }
   return this->array[elementIndex];
}


//////////////////////////////
//
// Collection::operator[] const
//

template<class type>
type Collection<type>::operator[](int elementIndex) const {
   if (elementIndex >= this->size) {
      std::cerr << "Error: accessing invalid array location " 
           << elementIndex 
           << " Maximum is " << this->size-1 << std::endl;
      exit(1);
   }
   return this->array[elementIndex];
}



//////////////////////////////
//
// shrinkTo
//

template<class type>
void Collection<type>::shrinkTo(long aSize) {
   if (aSize < this->getSize()) {
      exit(1);
   }

   type *temp = new type[aSize];
   for (int i=0; i<this->size; i++) {
      temp[i] = this->array[i];
   }
   delete [] this->array;
   this->array = temp;

   allocSize = aSize;
   if (size > allocSize) {
      size = allocSize;
   }
}


#endif  /* _COLLECTION_CPP_INCLUDED */



// md5sum: e5d20829760eaa880e5753116883784c Collection.cpp [20050403]
