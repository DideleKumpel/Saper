//
// Created by CEM on 27.03.2024.
//

#ifndef BAZADANYCH_OBSLUGABLEDUCIN_H
#define BAZADANYCH_OBSLUGABLEDUCIN_H

namespace CEH
{
    struct CinError {};
    void CinErrorHandler();
    bool CinErrorHandlerInt(long long int odpowiedz, bool range, long long int zakresP,long long int zakresK);
}

#endif //BAZADANYCH_OBSLUGABLEDUCIN_H
