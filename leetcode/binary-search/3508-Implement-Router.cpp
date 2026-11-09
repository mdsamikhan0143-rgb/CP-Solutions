class Router {
public:
    struct Packet {
        int source, destination, timestamp;

        bool operator==(const Packet& other) const {
            return source == other.source &&
                   destination == other.destination &&
                   timestamp == other.timestamp;
        }
    };

    struct PacketHash {
        size_t operator()(const Packet& p) const {
            size_t h1 = hash<int>()(p.source);
            size_t h2 = hash<int>()(p.destination);
            size_t h3 = hash<int>()(p.timestamp);

            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    int memoryLimit;

    deque<Packet> q;

    unordered_set<Packet, PacketHash> st;

    // Destination -> sorted timestamps
    unordered_map<int, vector<int>> times;

    // First active timestamp index for each destination
    unordered_map<int, int> head;

    Router(int memoryLimit) {
        this->memoryLimit = memoryLimit;
    }

    // Removes the oldest packet
    void removeOldest() {
        Packet p = q.front();
        q.pop_front();

        st.erase(p);

        head[p.destination]++;
    }

    bool addPacket(int source, int destination, int timestamp) {

        Packet p = {source, destination, timestamp};

        // Check duplicate
        if (st.count(p)) {
            return false;
        }

        // Remove oldest packet if memory is full
        if (q.size() == memoryLimit) {
            removeOldest();
        }

        // Add new packet
        q.push_back(p);
        st.insert(p);

        times[destination].push_back(timestamp);

        return true;
    }

    vector<int> forwardPacket() {

        if (q.empty()) {
            return {};
        }

        Packet p = q.front();

        removeOldest();

        return {p.source, p.destination, p.timestamp};
    }

    int getCount(int destination, int startTime, int endTime) {

        if (!times.count(destination)) {
            return 0;
        }

        auto &v = times[destination];

        int start = head[destination];

        // Find first timestamp >= startTime
        auto left = lower_bound(
            v.begin() + start, v.end(), startTime
        );

        // Find first timestamp > endTime
        auto right = upper_bound(
            v.begin() + start, v.end(), endTime
        );

        return right - left;
    }
};