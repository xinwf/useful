static int count = 0;

template <typename T>
T * SingletonTTS<T>::m_pInstance = nullptr;

template <typename T>
std::mutex SingletonTTS<T>::m_mutex;

template <typename T>
T * SingletonTTS<T>::Instance(){
    if(m_pInstance == nullptr){
        m_mutex.lock();
        if(m_pInstance == nullptr){
            m_pInstance = new T(count);
            std::cout << "&m_pInstance: " << &m_pInstance << ", m_pInstance: " << m_pInstance << "\n";
            ++count;
        }
        m_mutex.unlock();
    }
    return m_pInstance;
}

template <typename T>
T * SingletonTTS<T>::HasInstance(){
    if(m_pInstance == nullptr){
        std::cout << "No instance in this type.\n";
    }else{
        std::cout << "One instance in this class.\n";
    }
    return m_pInstance;
}

template <typename T>
void SingletonTTS<T>::Destroy(){
    if(m_pInstance){
        m_mutex.lock();
        if(m_pInstance){
            delete m_pInstance;
            m_pInstance = nullptr;
        }
        m_mutex.unlock();
    }
}