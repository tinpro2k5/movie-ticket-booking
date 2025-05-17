#include <cassert>
#include <iostream>
#include "../../include/utils/PricingRule.h"

class MockTicket : public Ticket {
public:
    MockTicket(double price, const std::string& showTime)
        : price(price), showTime(showTime) {}

    double getPrice() const override {
        return price;
    }

    std::string getShowTime() const override {
        return showTime;
    }

private:
    double price;
    std::string showTime;
};

class MockUser : public User {
public:
    MockUser(const std::string& email) : email(email) {}

    std::string getEmail() const override {
        return email;
    }

private:
    std::string email;
};

class MockSeat : public Seat {
public:
    MockSeat(bool isVip) : vip(isVip) {}

    bool isVip() const override {
        return vip;
    }

private:
    bool vip;
};

void test_student_discount() {
    MockTicket ticket(100000, "2025-05-17 15:00:00");
    MockUser user("abc@student.university.com");
    MockSeat seat(false);
    TicketContext ctx{ticket, user, seat};

    PricingContext pricing;
    pricing.addStrategy(std::make_shared<StudentDiscountStrategy>());
    double finalPrice = pricing.calculatePrice(ctx);
    assert(finalPrice == 80000);
    std::cout << "[PASS] test_student_discount\n";
}

void test_vip_seat() {
    MockTicket ticket(100000, "2025-05-17 15:00:00");
    MockUser user("abc@gmail.com");
    MockSeat seat(true);
    TicketContext ctx{ticket, user, seat};

    PricingContext pricing;
    pricing.addStrategy(std::make_shared<VipSeatStrategy>());
    double finalPrice = pricing.calculatePrice(ctx);
    assert(finalPrice == 120000);
    std::cout << "[PASS] test_vip_seat\n";
}

void test_evening_show() {
    MockTicket ticket(100000, "2025-05-17 19:00:00");
    MockUser user("abc@gmail.com");
    MockSeat seat(false);
    TicketContext ctx{ticket, user, seat};

    PricingContext pricing;
    pricing.addStrategy(std::make_shared<EveningShowStrategy>());
    double finalPrice = pricing.calculatePrice(ctx);
    assert(static_cast<int>(finalPrice) == 105000);
    std::cout << "[PASS] test_evening_show\n";
}

void test_holiday() {
    MockTicket ticket(100000, "2025-01-01 10:00:00");
    MockUser user("abc@gmail.com");
    MockSeat seat(false);
    TicketContext ctx{ticket, user, seat};

    PricingContext pricing;
    pricing.addStrategy(std::make_shared<HolidayStrategy>());
    double finalPrice = pricing.calculatePrice(ctx);
    assert(static_cast<int>(finalPrice) == 110000);
    std::cout << "[PASS] test_holiday\n";
}

void test_combined_strategies() {
    MockTicket ticket(100000, "2025-01-01 19:00:00");
    MockUser user("abc@student.university.com");
    MockSeat seat(true);
    TicketContext ctx{ticket, user, seat};

    PricingContext pricing;
    pricing.addStrategy(std::make_shared<StudentDiscountStrategy>());   // -20000 -> 80000
    pricing.addStrategy(std::make_shared<VipSeatStrategy>());           // +20000 -> 100000
    pricing.addStrategy(std::make_shared<EveningShowStrategy>());      // x1.05  -> 105000
    pricing.addStrategy(std::make_shared<HolidayStrategy>());          // x1.10  -> 115500

    double finalPrice = pricing.calculatePrice(ctx);
    assert(static_cast<int>(finalPrice) == 115500);
    std::cout << "[PASS] test_combined_strategies\n";
}

int main() {
    test_student_discount();
    test_vip_seat();
    test_evening_show();
    test_holiday();
    test_combined_strategies();
    std::cout << "✅ All tests passed!\n";
    return 0;
}
